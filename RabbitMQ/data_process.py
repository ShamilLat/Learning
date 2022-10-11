from enum import auto
import pika, sys, os

my_letter = ''
names_list = []
stop_msg = "STPCNSM"

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
    channel = connection.channel()

    channel.exchange_declare(exchange='letters', exchange_type='direct')

    channel.queue_declare(queue='get_first_letter')

    def get_my_letter(ch, method, properties, body):
        channel.stop_consuming()
        print("[R] Received %r" % body.decode())
        
        global my_letter
        my_letter = body.decode()
    
    def get_highway(ch, method, properties, body):
        if body.decode() != stop_msg:
            global names_list
            names_list.append(body.decode())
            print("[R] In get_highway", body.decode())
        else:
            channel.stop_consuming()
            print("[R] |" + my_letter + "| Got my streets")

    def output_my_streets(ch, method, properties, body):
        print("Test")

    # Берем по одной букве для каждого процесса (только одна)
    channel.basic_consume(queue='get_first_letter', on_message_callback=get_my_letter, auto_ack=True)
    print("[R] Waiting for letter.")
    channel.start_consuming()
    
    res = channel.queue_declare(queue=my_letter)
    # res = channel.queue_declare(queue=my_letter, auto_delete=True)
    # my_q_name = res.method.queue

    print("my letter =", my_letter)
    channel.queue_bind(queue=my_letter, exchange='letters', routing_key=my_letter)

    # Принимаем только улицы на свою букву
    channel.basic_consume(queue=my_letter, on_message_callback=get_highway, auto_ack=True)
    channel.start_consuming()

    # Принимаем указания от менеджера
    # channel.queue_declare(queue=my_letter, auto_delete=True)
    channel.basic_consume(queue=my_letter, on_message_callback=output_my_streets)
    channel.start_consuming()

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
