#!/usr/bin/env python3
import pika

connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
channel = connection.channel()

# Подключаемся к очереди с навзванием hello (если её нет то она создастся)
channel.queue_declare(queue='hello')

# at this point we are ready to send a message

# Отправка сообщения через default посредника, очередь hello, сообщение Hello World
channel.basic_publish(exchange='',
                      routing_key='hello',
                      body='Hello World!')
print(" [x] Sent 'Hello World!'")

connection.close()