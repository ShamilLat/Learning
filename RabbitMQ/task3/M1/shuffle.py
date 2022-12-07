import pika
import json
from sys import argv

# Чтобы понять, из какой папки потом открывать текстовик
number = argv[1]
k = int(argv[2])
end_msg = '__DONE__'
alphabet = 'abcdefghijklmnopqrstuvwxyz'
red_cnt = len(alphabet) // k

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

shuffle_queue_name = 'shuffle' + number
channel.queue_declare(queue=shuffle_queue_name, auto_delete=True)
channel.queue_bind(exchange='exchange', queue=shuffle_queue_name)

for i in range(k):
    reduce_queue_name = 'reduce' + str(i + 1)
    channel.queue_declare(queue=reduce_queue_name, auto_delete=True)
    channel.queue_bind(exchange='exchange', queue=reduce_queue_name)

words_dict = {}

def get_mapper_pair(channel, method, properties, body):
    global words_dict
    msg = json.loads(body.decode())
    key = list(msg.keys())
    val = list(msg.values())
    # print("shuf key val", key, val)
    if key[0] == end_msg:
        # print(words_dict)
        channel.stop_consuming()
        pairs = list(words_dict.items())
        for ii in pairs:
            # print("shuf send", ii)
            r_name = 'reduce' + str((alphabet.find(ii[0][0].lower()) // red_cnt) % k + 1)
            channel.basic_publish(exchange='exchange', routing_key=r_name, body=json.dumps(ii))
        for i in range(k):
            stop_msg = [end_msg, [1]]
            r_name = 'reduce' + str(i + 1)
            channel.basic_publish(exchange='exchange', routing_key=r_name, body=json.dumps(stop_msg))
        return 0
    if key[0] not in words_dict:
        words_dict[key[0]] = []
    
    words_dict[key[0]] += val

channel.basic_consume(shuffle_queue_name, on_message_callback=get_mapper_pair, auto_ack=True)
channel.start_consuming()
