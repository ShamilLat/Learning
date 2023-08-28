import pika
import json
from sys import argv

my_id = argv[1]
print("||||||||\n" + "MY ID IS " + my_id + "\n||||||||\n")
number_of_replicas = int(argv[2])
k = 3
# k = number_of_replicas // 3
# k = int(argv[3])

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

# получение от реплик сообщений
queue = 'rep' + my_id
channel.queue_declare(queue=queue, auto_delete=True)
channel.queue_bind(exchange='exchange', queue=queue)

for replica_id in range((number_of_replicas)):
    if (my_id != str(replica_id)):
        if (replica_id == 0):
            queue = 'mainrep-rep'
        else:
            queue = 'rep' + str(replica_id)
        channel.queue_declare(queue=queue, auto_delete=True)
        channel.queue_bind(exchange='exchange', queue=queue)


def get_rep_msg(channel, method, properties, body):
    msg = json.loads(body.decode())
    
    if versions[msg['msg'][0]] < msg['ver']:
        values[msg['msg'][0]] = msg['msg'][1:]
        versions[msg['msg'][0]] = msg['ver']

        # print("Replica " + my_id + " - update: " + msg['msg'][0] + "=" + msg['msg'][1:] + ", version = " + str(versions[msg['msg'][0]]))
        print("Replica " + my_id + " - update:")
        print(values['x'], versions['x'])
        print(values['y'], versions['y'])
        print(values['z'], versions['z'])

        # отправка подтверждения главной реплике
        say_ok = {'replica_id': my_id, 'ok_msg': True}
        queue = 'mainrep-rep'
        channel.basic_publish(exchange='exchange', routing_key=queue, body=json.dumps(say_ok))
        
        # отправляем другим репликам
        for i in range(k):
            id = int(my_id) * k + 1 + i
            if id > number_of_replicas:
                id %= number_of_replicas
            replica_id = str(id)
            if (my_id != replica_id):
                queue = 'rep' + replica_id
                channel.basic_publish(exchange='exchange', routing_key=queue, body=json.dumps(msg))


queue = 'rep' + my_id
channel.basic_consume(queue, on_message_callback=get_rep_msg, auto_ack=True)
channel.start_consuming()
