from itertools import count
import sys, os
import subprocess as sp
import shlex
import pika

count_processes = 0
starter_message = "[S] Starter"

def main():
    # sp.call(["python3", "test.py"])
    # sp.call(["python3", "test.py"])

    etl_cmd = 'python3 etl.py'
    cmd_args = shlex.split(etl_cmd)

    # sp.run(args=cmd_args)
    etl_pr = sp.Popen(cmd_args, stdin=None, stdout=None, stderr=None, close_fds=True)

    # p2 = sp.Popen(cmd, stderr=sp.STDOUT, shell=True)
    
    connection = pika.BlockingConnection(pika.ConnectionParameters(host = 'localhost'))
    channel = connection.channel()

    starter_queue_name = 'starter_queue'
    channel.queue_declare(queue=starter_queue_name)

    def get_number(ch, method, properties, body):
        channel.stop_consuming()
        global count_processes 
        count_processes = int(body.decode())   
        print(starter_message, "got count_processes =", count_processes)     

    channel.basic_consume(queue=starter_queue_name, on_message_callback=get_number, auto_ack=True)
    channel.start_consuming()

    data_processes = []

    # data_pr_cmd = "python3 receive.py"
    data_pr_cmd = "python3 data_process.py"
    cmd_args = shlex.split(data_pr_cmd)
    for i in range(0, count_processes):
        sp.Popen(cmd_args, stdin=None, stdout=None, stderr=None, close_fds=True)
        # sp.run(cmd_args)
        # data_processes.append(pr)

    manager_cmd = "python3 manager.py"
    client_cmd = "python3 client.py"
    cmd_args = shlex.split(manager_cmd)
    sp.Popen(cmd_args, stdin=None, stdout=None, stderr=None, close_fds=True)
    # cmd_args = shlex.split(client_cmd)
    # sp.Popen(cmd_args, stdin=None, stdout=None, stderr=None, close_fds=True)

    # p1 = sp.Popen(args, stdin=sp.PIPE, stderr=sp.STDOUT)
    # p2 = sp.Popen(args, stdin=sp.PIPE, stderr=sp.STDOUT)

    connection.close()

    # p1.terminate()
    # p2.terminate()

    # print("Im here")

    # p1.communicate(input=5)

    # print("Im here 2")

    # p2.communicate(input=2)
    # r1 = p1.communicate()[0]
    # r2 = p2.communicate()[0]

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("Interrupted")
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)
