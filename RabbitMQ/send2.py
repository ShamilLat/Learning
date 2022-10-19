#!/usr/bin/env python3
import pika, sys, os
import time
from random import seed
from random import randint

def main():

    connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
    channel = connection.channel()

    channel.exchange_declare(exchange='letters', exchange_type='direct')

    random_letters = 'апмф'

    channel.queue_declare(queue='get_first_letter')
    for i in random_letters:
        channel.basic_publish(exchange='', routing_key='get_first_letter', body=i)

    seed(1)

    while True:
        value = randint(0, 3)
        time.sleep(3)
        
        channel.basic_publish(exchange='letters',
                            routing_key=random_letters[value],
                            body=random_letters[value])
        message = "Sended " + random_letters[value] + " with routing key |" + random_letters[value] + "|"
        print(message)
    # at this point we are ready to send a message

    # Отправка сообщения через default посредника, очередь hello, сообщение Hello World

    connection.close()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("Interrupted")
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)