import pika
from sys import argv
import json
from hexlet import pairs

# Чтобы понять, из какой папки потом открывать текстовик
number = argv[1]
end_msg = '__DONE__'

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

mapper_queue_name = 'mapper' + number
channel.queue_declare(queue=mapper_queue_name, auto_delete=True)
channel.queue_bind(exchange='exchange', queue=mapper_queue_name)

shuffle_queue_name = 'shuffle' + number
channel.queue_declare(queue=shuffle_queue_name, auto_delete=True)
channel.queue_bind(exchange='exchange', queue=shuffle_queue_name)

def get_splitter_word(channel, method, properties, body):
    msg = body.decode()
    pair = {msg: 1}
    channel.basic_publish(exchange='exchange', routing_key=shuffle_queue_name, body=json.dumps(pair))
    if msg == end_msg:
        channel.stop_consuming()
        return 0
    
channel.basic_consume(mapper_queue_name, on_message_callback=get_splitter_word, auto_ack=True)
channel.start_consuming()
