import os
import pika
import json
from sys import argv
import math

txt_folder = argv[1]
# n = int(argv[2])
# k = int(argv[3])
end_msg = '__DONE__'

with open("../input.txt", "r") as f:
    n = int(f.readline())
    k = int(f.readline())

# разбрасывает текстовые файлы по Mn папкам
for i in range(n):
    os.system("cp " + txt_folder + "/" + str(i + 1) + ".txt " + txt_folder + "/../M" + str(i + 1) + "/text.txt")

for i in range(n):
    os.system("python3 ../M" + str(i + 1) + "/splitter.py " + str(i + 1))

for i in range(n):
    os.system("python3 ../M" + str(i + 1) + "/mapper.py " + str(i + 1))

for i in range(n):
    os.system("python3 ../M" + str(i + 1) + "/shuffle.py " + str(i + 1) + " " + str(k))

for i in range(k):
    os.system("python3 ../R" + str(i + 1) + "/reducer.py " + str(i + 1) + " " + str(n))

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()
channel.exchange_declare(exchange='exchange', exchange_type='direct')

master_queue_name = 'master'
channel.queue_declare(queue=master_queue_name, auto_delete=True)
channel.queue_bind(exchange='exchange', queue=master_queue_name)

master_cnt_queue_name = 'master_counts'
channel.queue_declare(queue=master_cnt_queue_name, auto_delete=True)
channel.queue_bind(exchange='exchange', queue=master_cnt_queue_name)

cnts = {}
txts_cnt = {}

red_cnts_counter = 0

def get_res(channel, method, properties, body):
    msg = json.loads(body)
    cnts[msg[0].lower()] = msg[1]

def get_count(channel, method, properties, body):
    global red_cnts_counter
    msg = json.loads(body)
    # print("master get cnt", msg)
    if msg[0] == end_msg:
        red_cnts_counter += 1
        if red_cnts_counter == k:
            channel.stop_consuming()
            return 0
    else:
        if msg[0] not in txts_cnt:
            txts_cnt[msg[0].lower()] = 0
    
        txts_cnt[msg[0].lower()] = msg[1]


channel.basic_consume(master_queue_name, on_message_callback=get_res, auto_ack=True)
channel.basic_consume(master_cnt_queue_name, on_message_callback=get_count, auto_ack=True)
channel.start_consuming()

tf = {}
idf = {}

words_cnt = sum(cnts.values())
print("Total words:", words_cnt)
words = cnts.keys()

# print(cnts)
# print()
# print(txts_cnt)
# print()

for i in words:
    tf[i] = cnts[i] / words_cnt

for i in words:
    idf[i] = math.log(n / txts_cnt[i], 10)

ans = sorted(cnts.items())

for i in ans:
    print(f'{i[0]}\t{i[1]}\t{tf[i[0]] * idf[i[0]]}')

