import pika
import sys, os

c_to_m_str = "c_to_m"
m_to_c_str = "m_to_c"
stop_msg = "STPCNSM" # Stop Consume
signal_msg = 'NDLST' # Need List
m_str = "to_manager"
m_str2 = "manager_to_"
etl_to_m_str = 'etl_to_manager'
letters_list = []
end_str = "end_"

client_connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
client_channel = client_connection.channel()
client_channel.queue_declare(queue=m_to_c_str)
client_channel.queue_declare(queue=c_to_m_str)

data_connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
data_channel = data_connection.channel()
data_channel.queue_declare(queue=m_str)
data_channel.exchange_declare(exchange='manager', exchange_type='direct')

etl_connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
etl_channel = etl_connection.channel()
etl_channel.queue_declare(queue=etl_to_m_str, auto_delete=True)

def get_letter(ch, method, properties, body):
    if body.decode() != stop_msg:
        letters_list.append(body.decode())
    else:
        etl_channel.stop_consuming()
        print("[M] Start working")

def get_command(h, method, properties, body):
    print("[M] I got command", body.decode())
    
    def get_name(ch, method, properties, body):
        if body.decode() != stop_msg:
            client_channel.basic_publish(exchange='', routing_key=m_to_c_str, body=body.decode())
        else:
            client_channel.basic_publish(exchange='', routing_key=m_to_c_str, body=stop_msg)
            data_channel.stop_consuming()
    
    if body.decode() == end_str:
        for i in letters_list:
            data_channel.basic_publish(exchange='manager', routing_key=m_str2+i, body=end_str)
        return

    if body.decode() != stop_msg:
        if body.decode() in letters_list:
            data_channel.basic_publish(exchange='manager', routing_key=m_str2+(body.decode()).lower(), body=signal_msg)
            print("[M] Sended a signal_msg to " + m_str2+(body.decode()).lower())
            data_channel.basic_consume(queue=m_str, on_message_callback=get_name, auto_ack=True)
            data_channel.start_consuming()
        else:
            data_channel.basic_publish(exchange='', routing_key=m_to_c_str, body='None')
            data_channel.basic_publish(exchange='', routing_key=m_to_c_str, body=stop_msg)
            
    else:
        client_channel.stop_consuming()
        return


etl_channel.basic_consume(queue=etl_to_m_str, on_message_callback=get_letter, auto_ack=True)
etl_channel.start_consuming()

print("[M]", letters_list)

client_channel.basic_consume(queue=c_to_m_str, on_message_callback=get_command, auto_ack=True)
client_channel.start_consuming()

data_connection.close()
client_connection.close()
etl_connection.close()
