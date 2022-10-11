import sys, os
import subprocess as sp
import shlex

def main():

    # sp.call(["python3", "test.py"])
    # sp.call(["python3", "test.py"])

    cmd = 'python3 eml.py'
    args = shlex.split(cmd)

    # p1 = sp.Popen(args, stdin=sp.PIPE, stderr=sp.STDOUT)
    # p2 = sp.Popen(args, stdin=sp.PIPE, stderr=sp.STDOUT)

    p1 = sp.Popen(args, stderr=sp.STDOUT)
    p2 = sp.Popen(cmd, stderr=sp.STDOUT, shell=True)


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
