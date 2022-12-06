import pika
from sys import argv

#  Чтобы понять, из какой папки потом открывать текстовик
number = argv[1]

with open("../M" + number + "/text.txt", "r") as f:
    words = f.read().split()

print(words)

connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
channel = connection.channel()
channel_manager = connection.channel()
