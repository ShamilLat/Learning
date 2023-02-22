import os
from applescript import tell

replicas_num = 7
k = 3
# Command = 'python3 .py'
# file_way = ' /Users/2lapsha1/MSU_learning/RabbitMQ/task2/'
file_way = ""

tell.app('Terminal', 'do script "python3 ' + file_way + 'main_rep.py ' + str(replicas_num) + '"') 
# tell.app('Terminal', 'do script "python3' + file_way + 'client.py"') 

for i in range(replicas_num):
    tell.app('Terminal', 'do script "python3 ' + file_way + 'rep.py ' + str(i + 1) + " " + str(replicas_num) + '"') 


input_data = input()
while input_data != "end":
    input_data = input()

os.system('killall Terminal')