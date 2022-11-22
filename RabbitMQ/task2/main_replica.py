# cd C:\Program Files\RabbitMQ Server\rabbitmq_server-3.10.6\sbin
# rabbitmq-service stop
# rabbitmq-service start
import pika
import json
from sys import argv

own_replica_id = '0'
number_of_replicas = int(argv[1])
#k = number_of_replicas // 3 + 1
k = int(argv[2])
responce_count = 1

data = {}
data['x'] = {'val': 0, 'ver': 0}
data['y'] = {'val': 0, 'ver': 0}
data['z'] = {'val': 0, 'ver': 0}

print("INFO: replica " + own_replica_id + " started working")

# установка связи и объявление всех очередей
connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

# очередь для прослушки сообщений от клиента
channel.queue_declare(queue='client-mainreplica')
channel.queue_bind(exchange='exchange', queue='client-mainreplica')

# очередь для прослушки сообщений от других реплик
channel.queue_declare(queue='mainreplica-replica')
channel.queue_bind(exchange='exchange', queue='mainreplica-replica')

# очереди для отравки сообщений репликам
for replica_id in range(number_of_replicas):
    if (own_replica_id != str(replica_id)):
        queue = 'replica' + str(replica_id)
        channel.queue_declare(queue=queue)
        channel.queue_bind(exchange='exchange', queue=queue)

def handle_client_message(channel, method, properties, body):
    msg = json.loads(body.decode())
    
    # добавляем информацию о версии
    data[msg['var_name']]['ver'] += 1
    msg['var_ver'] = data[msg['var_name']]['ver']
    
    # меняем данные на главной реплике
    data[msg['var_name']]['val'] = msg['var_val']
    
    # логируем именения данных
    # print(msg)
    print("INFO: main replica updated value of variable\t" + msg['var_name'] + " = " + str(msg['var_val']))
    
    # отправляем сообщение другим репликам
    for shift in range(k):
        replica_id = str((int(own_replica_id) + 1 + k * shift) % number_of_replicas)
        queue = 'replica' + replica_id
        channel.basic_publish(exchange='exchange', routing_key=queue, body=json.dumps(msg))

def handle_replica_message(channel, method, properties, body):
    global responce_count
    msg = json.loads(body.decode())
    if 'var_val' in msg:
        if data[msg['var_name']]['ver'] < msg['var_ver']:
            data[msg['var_name']]['val'] = msg['var_val']
            data[msg['var_name']]['ver'] = msg['var_ver']
    elif 'responce' in msg:
        if msg['responce'] == "ok":
            responce_count += 1
            print("INFO: main replica get responce from replica " + msg['replica_id'])
    if responce_count == number_of_replicas:
        responce_count = 1
        print("INFO: all replicas updated value of variable " + msg['var_name'])

# for replica_id in range(number_of_replicas):
#     if (own_replica_id != str(replica_id)):
#         queue = 'mainreplica-replica' + str(replica_id)
#         channel.basic_consume(queue, handle_replica_message)
channel.basic_consume('mainreplica-replica', handle_replica_message)
channel.basic_consume('client-mainreplica', handle_client_message)
channel.start_consuming()
