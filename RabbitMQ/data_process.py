from enum import auto
import pika, sys, os

my_letter = ''
names_list = []
stop_msg = "STPCNSM"
signal_msg = 'NDLST' # Need List
m_str = "to_manager"
m_str2 = "manager_to_"
end_str = "end_"

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
    channel = connection.channel()
    channel_manager = connection.channel()

    channel.exchange_declare(exchange='letters', exchange_type='direct')

    channel.queue_declare(queue='get_first_letter', auto_delete=True)

    def get_my_letter(ch, method, properties, body):
        channel.stop_consuming()
        
        global my_letter
        my_letter = body.decode()
    
    def get_highway(ch, method, properties, body):
        if body.decode() != stop_msg:
            global names_list
            names_list.append(body.decode())
        else:
            channel.stop_consuming()

    def output_my_streets(ch, method, properties, body):
        print("[R] |" + my_letter + "| Got signal")
        if body.decode() == signal_msg:
            for i in names_list:
                channel_manager.basic_publish(exchange='manager', routing_key=m_str, body=i)
            channel_manager.basic_publish(exchange='manager', routing_key=m_str, body=stop_msg)
        elif body.decode() == end_str:
            channel.stop_consuming()
        
    # Берем по одной букве для каждого процесса (только одна)
    channel.basic_consume(queue='get_first_letter', on_message_callback=get_my_letter, auto_ack=True)
    channel.start_consuming()
    
    
    print("my letter =", my_letter)
    channel.queue_declare(queue=my_letter)
    channel.queue_bind(queue=my_letter, exchange='letters', routing_key=my_letter)

    # Принимаем только улицы на свою букву
    channel.basic_consume(queue=my_letter, on_message_callback=get_highway, auto_ack=True)
    channel.start_consuming()

    # Принимаем указания от менеджера
    channel_manager.exchange_declare(exchange='manager', exchange_type='direct')
    channel_manager.queue_declare(queue=m_str)
    channel_manager.queue_bind(queue=m_str, exchange='manager', routing_key=m_str)

    channel.exchange_declare(exchange='manager', exchange_type='direct')
    channel.queue_declare(queue=(m_str2+my_letter))
    channel.queue_bind(queue=(m_str2+my_letter), exchange='manager', routing_key=(m_str2+my_letter))
    channel.basic_consume(queue=(m_str2+my_letter), on_message_callback=output_my_streets, auto_ack=True)
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
