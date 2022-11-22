import pika
import json
from sys import argv

own_replica_id = argv[1]
number_of_replicas = int(argv[2])
#k = number_of_replicas // 3 + 1
k = int(argv[3])

data = {}
data['x'] = {'val': 0, 'ver': 0}
data['y'] = {'val': 0, 'ver': 0}
data['z'] = {'val': 0, 'ver': 0}

print("INFO: replica " + own_replica_id + " started working")

# установка связи и объявление всех очередей
connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

# очередь для прослушки сообщений от реплик
queue = 'replica' + own_replica_id
channel.queue_declare(queue=queue)
channel.queue_bind(exchange='exchange', queue=queue)

# очереди для отправки сообщений
for replica_id in range((number_of_replicas)):
    if (own_replica_id != str(replica_id)):
        if (replica_id == 0):
            queue = 'mainreplica-replica'
        else:
            queue = 'replica' + str(replica_id)
        channel.queue_declare(queue=queue)
        channel.queue_bind(exchange='exchange', queue=queue)


def handle_replica_message(channel, method, properties, body):
    msg = json.loads(body.decode())
    # проверка данных на актуальность
    if data[msg['var_name']]['ver'] < msg['var_ver']:
        # обновление данных на реплике
        data[msg['var_name']]['val'] = msg['var_val']
        data[msg['var_name']]['ver'] = msg['var_ver']
        
        # логирование
        print("INFO: replica " + own_replica_id + " updated value of variable\t" + msg['var_name'] + " = " + str(msg['var_val']))
        
        # отправка подтверждения главной реплике
        confirm = {}
        confirm['var_name'] = json.loads(body.decode())['var_name']
        confirm['replica_id'] = own_replica_id
        confirm['responce'] = "ok"
        
        # print(confirm)
        queue = 'mainreplica-replica'
        channel.basic_publish(exchange='exchange', routing_key=queue, body=json.dumps(confirm))
        
        # рассылка данных другим репликам
        for shift in range(k):
            replica_id = str((int(own_replica_id) + 1 + k*shift) % number_of_replicas)
            if (own_replica_id != replica_id):
                queue = 'replica' + replica_id
                channel.basic_publish(exchange='exchange', routing_key=queue, body=json.dumps(msg))


queue = 'replica' + own_replica_id
channel.basic_consume(queue, handle_replica_message)
channel.start_consuming()
