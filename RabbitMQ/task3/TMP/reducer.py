import pika
import json
from sys import argv

# Чтобы понять, из какой папки потом открывать текстовик
number = argv[1]
n = int(argv[2])
end_msg = '__DONE__'

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

reduce_queue_name = 'reduce' + number
channel.queue_declare(queue=reduce_queue_name, auto_delete=True)
channel.queue_bind(exchange='exchange', queue=reduce_queue_name)

master_queue_name = 'master'
channel.queue_declare(queue=master_queue_name, auto_delete=True)
channel.queue_bind(exchange='exchange', queue=master_queue_name)

results = {}
shuffle_count = 0

def get_shuffle_dict(channel, method, properties, body):
    global shuffle_count
    msg = json.loads(body.decode())
    # print("red get msg", msg)
    if msg[0] == end_msg:
        shuffle_count += 1
        if shuffle_count == n:
            channel.stop_consuming()
            pairs = list(results.items())
            for ii in pairs:
                # print("red send", ii)
                channel.basic_publish(exchange='exchange', routing_key=master_queue_name, body=json.dumps(ii))
            stop_msg = [end_msg, 1]
            channel.basic_publish(exchange='exchange', routing_key=master_queue_name, body=json.dumps(stop_msg))
            return 0
    else:
        if msg[0] not in results:
            results[msg[0]] = 0
    
        results[msg[0]] += sum(msg[1])
    # print(msg[0], sum(msg[1]))

channel.basic_consume(reduce_queue_name, on_message_callback=get_shuffle_dict, auto_ack=True)
channel.start_consuming()