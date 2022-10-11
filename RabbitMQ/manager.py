import pika
import sys, os

manager_queue_name = 'manager_queue'
client_queue_name = 'client_queue'
stop_msg = "STPCNSM" # Stop Consume
signal_msg = 'NDLST' # Need List
names_list = []
m_str = "_manager"

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
    channel = connection.channel()

    letters_list = []

    def get_letter(ch, method, properties, body):
        if body.decode() != stop_msg:
            letters_list.append(body.decode())
        else:
            print("[M] Stop getting letters")
            channel.stop_consuming()

    def get_name(ch, method, properties, body):
        if body.decode() != stop_msg:
            names_list.append(body.decode())
        else:
            print("[M] Got list of names")
            print(names_list)
            channel.stop_consuming()

    def get_command(ch, method, properties, body):
        print("[M] I got command", body.decode())
        if body.decode() != stop_msg:
            channel.basic_publish(exchange='manager', routing_key=(body.decode()).lower()+m_str, body=signal_msg)
            print("[M] Sended a signal_msg to " + (body.decode()).lower())
            channel.basic_consume(queue=(body.decode()).lower()+m_str, on_message_callback=get_name, auto_ack=True)
            channel.start_consuming()
        else:
            print("[M] Stop working with client")
            channel.stop_consuming()

    # Получает от etl все буквы
    channel.queue_declare(queue=manager_queue_name, auto_delete=True)
    channel.basic_consume(queue=manager_queue_name, on_message_callback=get_letter, auto_ack=True)
    channel.start_consuming()

    print("[M] Got all letters from etl")

    # подключаемся к обменникам
    # channel.exchange_declare(exchange='letters', exchange_type='direct')
    channel.exchange_declare(exchange='manager', exchange_type='direct', auto_delete=True)

    # Общается с клиентом
    channel.queue_declare(queue=client_queue_name, auto_delete=True)
    channel.basic_consume(queue=client_queue_name, on_message_callback=get_command, auto_ack=True)
    # print("[M] Im here")
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