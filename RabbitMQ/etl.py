import osmium as osm
import pika
import sys, os
import time

class OSMHandler(osm.SimpleHandler): 
    def __init__(self): 
        osm.SimpleHandler.__init__(self) 
        self.highways_data = []

    def way(self, w): 
        if w.tags.get('highway') == 'residential' and 'name' in w.tags:
            self.highways_data.append(w.tags['name']) 

stop_msg = "STPCNSM" # Stop Consume

def main():
    osmhandler = OSMHandler() 
    osmhandler.apply_file("map.osm") 

    # Убираем повторения в названиях улиц
    osmhandler.highways_data = list(dict.fromkeys(osmhandler.highways_data))

    # Удаляем слово "Улица"
    highway_russian = 'улица'
    for i in range(0, len(osmhandler.highways_data)):
        if highway_russian in osmhandler.highways_data[i].lower():
            osmhandler.highways_data[i] = (osmhandler.highways_data[i].replace('улица', '')).strip()

    # Убираем повторерния в первых буквах улиц
    letters_list = list(dict.fromkeys((list(i.lower()[0] for i in osmhandler.highways_data))))
    
    highways_dict = {}

    # Словарь: ключ = первая буква улицы, значение = список улиц на эту букву
    for i in osmhandler.highways_data:
        highways_dict[i.lower()[0]] = []

    for i in osmhandler.highways_data:
        highways_dict[i.lower()[0]].append(i)

    #PIKA
    connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
    channel = connection.channel()

    starter_queue_name = 'starter_queue'
    etl_to_m_str = 'etl_to_manager'
    
    # Отправляем в Стартер число, сколько процессов нам понадобятся
    channel.queue_declare(queue=starter_queue_name, auto_delete=True)
    channel.basic_publish(exchange='', routing_key=starter_queue_name, body=str(len(letters_list)))

    # Отправляем в менеджер все буквы
    channel.queue_declare(queue=etl_to_m_str, auto_delete=True)
    for i in letters_list:
        channel.basic_publish(exchange='', routing_key=etl_to_m_str, body=i)
    channel.basic_publish(exchange='', routing_key=etl_to_m_str, body=stop_msg)

    # Отправка в get_first_letter первые буквы доступных нам улиц
    channel.queue_declare(queue='get_first_letter', auto_delete=True)
    for i in letters_list:
        channel.basic_publish(exchange='', routing_key='get_first_letter', body=i)

    # print(letters_list)

    channel.exchange_declare(exchange='letters', exchange_type='direct')
    
    time.sleep(1)
    for i in letters_list:
        for h_name in highways_dict[i]:
            channel.basic_publish(exchange='letters',
                                routing_key=i,
                                body=h_name)
            message = "[E] Sended " + h_name + " with routing key |" + i + "|"
            # print(message)

    # Даем процессам-хранителям понять, что ждать улиц больше не надо
    for i in letters_list:
        channel.basic_publish(exchange='letters', routing_key=i, body=stop_msg)

    # Отправляем в Менеджер сообщение, что он может начинать работу
    channel.basic_publish(exchange='', routing_key=etl_to_m_str, body=stop_msg)
    
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
