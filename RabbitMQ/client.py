import pika
import sys, os

c_to_m_str = "c_to_m"
m_to_c_str = "m_to_c"
end_str = "end_"
check_end = 1
stop_msg = "STPCNSM"

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
    manager_channel = connection.channel()

    manager_channel.queue_declare(queue=c_to_m_str)
    manager_channel.queue_declare(queue=m_to_c_str)

    global check_end

    def callback(ch, method, properties, body):
        # if body.decode() != stop_msg or body.decode() != 'None':
        if body.decode() != stop_msg:
            # print("[C] Get " + body.decode())
            print(body.decode())
        else:
            manager_channel.stop_consuming()
        
    while check_end:
        x=str(input())

        manager_channel.basic_publish(exchange='', routing_key=c_to_m_str, body=x)
        print("[C] Sended to manager " + x + " with rt = " + c_to_m_str)

        if x == end_str:
            check_end = 0

        manager_channel.basic_consume(queue=m_to_c_str, on_message_callback=callback, auto_ack=True)
        manager_channel.start_consuming()

    connection.close()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        # print("Interrupted")
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)
