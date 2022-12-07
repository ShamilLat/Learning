import pika
from sys import argv

# Чтобы понять, из какой папки потом открывать текстовик
number = argv[1]
end_msg = '__DONE__'

with open("../M" + number + "/text.txt", "r") as f:
    words = f.read().split()

# print(words)

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

mapper_queue_name = 'mapper' + number
channel.queue_declare(queue=mapper_queue_name, auto_delete=True)
channel.queue_bind(exchange='exchange', queue=mapper_queue_name)

for word in words:
    channel.basic_publish(exchange='exchange', routing_key=mapper_queue_name, body=word)

channel.basic_publish(exchange='exchange', routing_key=mapper_queue_name, body=end_msg)
