import pika
import json
from sys import argv

my_id = '0'
print("||||||||\n" + "MY ID IS " + my_id + "\n||||||||\n")
number_of_replicas = int(argv[1])
k = 3
# k = int(argv[2])

values = {}
values['x'] = ""
values['y'] = ""
values['z'] = ""

versions = {}
versions['x'] = 0
versions['y'] = 0
versions['z'] = 0

print("Started working")

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

# очередь-клиент
channel.queue_declare(queue='client-mainrep', auto_delete=True)
channel.queue_bind(exchange='exchange', queue='client-mainrep')

# очередь-реплики
channel.queue_declare(queue='mainrep-rep', auto_delete=True)
channel.queue_bind(exchange='exchange', queue='mainrep-rep')

for replica_id in range(number_of_replicas):
    if (my_id != str(replica_id)):
        tmp = 'rep' + str(replica_id)
        channel.queue_declare(queue=tmp, auto_delete=True)
        channel.queue_bind(exchange='exchange', queue=tmp)

def get_client_msg(channel, method, properties, body):
    msg = body.decode()
    print(msg)

    versions[msg[0]] += 1
    values[msg[0]] = msg[1:]
    
    # print("Main replica - update: " + msg[0] + "=" + msg[1:] + ", version = " + str(versions[msg[0]]))
    print("Main replica - update:")
    print(values['x'], versions['x'])
    print(values['y'], versions['y'])
    print(values['z'], versions['z'])


    # отправляем сообщение другим репликам
    for i in range(k):
        replica_id = str((int(my_id) * k + 1 + i) % number_of_replicas)
        queue = 'rep' + replica_id
        send_tmp = {"msg": msg, "ver": versions[msg[0]]}
        channel.basic_publish(exchange='exchange', routing_key=queue, body=json.dumps(send_tmp))

rep_counter = 0

def get_rep_msg(channel, method, properties, body):
    global rep_counter
    msg = json.loads(body.decode())
    if 'msg' in msg:
        if versions[msg['msg'][0]] < msg['ver']:
            values[msg['msg'][0]] = msg['msg'][1:]
            versions[msg['msg'][0]] = msg['ver']
    elif 'ok_msg' in msg:
        if msg['ok_msg']:
            rep_counter += 1
            print("Main replica - get responce from replica " + msg['replica_id'])
    if rep_counter == number_of_replicas:
        rep_counter = 0
        print("Main replica - all replicas updated value")


channel.basic_consume('client-mainrep', on_message_callback=get_client_msg, auto_ack=True)
channel.basic_consume('mainrep-rep', on_message_callback=get_rep_msg, auto_ack=True)
channel.start_consuming()
