import pika

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

channel.queue_declare(queue='client-mainrep', auto_delete=True)
channel.queue_bind(exchange='exchange', queue='client-mainrep')

while True:
    var_name = input("Letter: ")
    var_value = input("Value: ")
    
    msg = var_name.lower() + var_value
    
    # отправка посылки, ожидание следующего ввода
    channel.basic_publish(exchange='exchange', routing_key='client-mainrep', body=msg)
