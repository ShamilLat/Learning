import pika
from sys import argv

#  Чтобы понять, из какой папки потом открывать текстовик
number = argv[1]

with open("../M" + number + "/text.txt", "r") as f:
    words = f.read().split()

print(words)

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

channel.queue_declare(queue='M' + number, auto_delete=True)
channel.queue_bind(exchange='exchange', queue='M' + number)
