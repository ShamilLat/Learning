from enum import auto
import pika, sys, os

my_letter = ''
names_list = []
stop_msg = "STPCNSM"
signal_msg = 'NDLST' # Need List
m_str = "_manager"

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
            # print("[R] In get_highway", body.decode())
        else:
            channel.stop_consuming()
            print("[R] |" + my_letter + "| Got my streets")

    def output_my_streets(ch, method, properties, body):
        if body.decode() == signal_msg:
            for i in names_list:
                channel.basic_publish(exchange='manager', routing_key=my_letter, body=i)
            channel.basic_publish(exchange='manager', routing_key=my_letter, body=stop_msg)
        else:
            print('[R] Not a Signal |' + body.decode() + '|' )
        
    # Берем по одной букве для каждого процесса (только одна)
    channel.basic_consume(queue='get_first_letter', on_message_callback=get_my_letter, auto_ack=True)
    print("[R] Waiting for letter.")
    channel.start_consuming()
    
    
    print("my letter =", my_letter)
    channel.queue_declare(queue=my_letter)
    channel.queue_bind(queue=my_letter, exchange='letters', routing_key=my_letter)

    # Принимаем только улицы на свою букву
    channel.basic_consume(queue=my_letter, on_message_callback=get_highway, auto_ack=True)
    channel.start_consuming()

    # Принимаем указания от менеджера
    channel.exchange_declare(exchange='manager', exchange_type='direct', auto_delete=True)
    channel.queue_declare(queue=(my_letter+m_str))
    channel.queue_bind(queue=(my_letter+m_str), exchange='manager', routing_key=(my_letter+m_str))
    channel.basic_consume(queue=(my_letter+m_str), on_message_callback=output_my_streets, auto_ack=True)
    print("[R] Waiting for signal")
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
