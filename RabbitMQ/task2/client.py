import pika
import json

avail_input_data = "xyzXYZ"

# установка связи и объявление всех очередей
connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

channel.queue_declare(queue='client-mainreplica')
channel.queue_bind(exchange='exchange', queue='client-mainreplica')

while True:
    var_name = input("Enter a variable name: ")
    var_value = input("Enter a variable value: ")
    while len(var_name) != 1 or not var_name in avail_input_data or not var_value.lstrip("-").isnumeric():
        var_name = input("Incorrect input. Try again.\nEnter a variable name: ")
        var_value = input("Enter a variable value: ")
    
    # формирование посылки главной реплике
    msg = {}
    msg['var_name'] = var_name.lower()
    msg['var_val'] = int(var_value)
    print(int(var_value))
    # отправка посылки, ожидание следующего ввода
    channel.basic_publish(exchange='exchange', routing_key='client-mainreplica', body=json.dumps(msg))
