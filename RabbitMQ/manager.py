import pika
import sys, os

manager_queue_name = 'manager_queue'
client_queue_name = 'client_queue'
stop_msg = "STPCNSM" # Stop Consume

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
    channel = connection.channel()

    channel.queue_declare(queue=manager_queue_name, auto_delete=True)
    letters_list = []

    def get_letter(ch, method, properties, body):
        if body.decode() != stop_msg:
            letters_list.append(body.decode())
        else:
            channel.stop_consuming()

    def get_command(ch, method, properties, body):
        print(1)

    channel.basic_consume(queue=manager_queue_name, on_message_callback=get_letter, auto_ack=True)
    channel.start_consuming()

    channel.queue_declare(queue=client_queue_name, auto_delete=True)
    channel.basic_consume(queue=client_queue_name, on_message_callback=get_command, auto_ack=True)
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