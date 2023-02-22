from sys import argv
from random import randint
import os

# clear
os.system("python3 /Users/2lapsha1/MSU_learning/RabbitMQ/task3/clear.py")

# generate folders and txt files    
words = ['ananas', 'banana', 'apple', 'grape', 'pomegranate', 'plum', 'cat', 'dog', 'horse', 'cow', 'duck', 'zebra', 'lion', 'parrot', 'way', 'universe', 'void', 'yellow', 'red', 'blue', 'green', 'orange', 'white', 'telephone', 'computer', 'fridge', 'table', 'wave', 'monitor', 'news', 'cupboard', 'letter', 'store', 'power', 'huge', 'over', 'wonderfull', 'xcode', 'iphone', 'peace', 'tech', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', 'ten', 'hundred', 'tablet', 'water', 'plane', 'car', 'ship', 'tea', 'coffee', 'drink', 'lunch']
with open("input.txt", "r") as input_f:
    n = int(input_f.readline())
    k = int(input_f.readline())

for i in range(n):
    folder_name = "M" + str(i + 1)
    os.system("mkdir " + folder_name)
    os.system("cp TMP/splitter.py " + folder_name + "/splitter.py")
    os.system("cp TMP/mapper.py " + folder_name + "/mapper.py")
    os.system("cp TMP/shuffle.py " + folder_name + "/shuffle.py")
    with open("Txt/" + str(i + 1) + ".txt", "w") as f:
        w_cnt = randint(1, 3)
        for j in range(w_cnt):
            print(words[randint(0, len(words)) - 1], end=' ', file=f)

for i in range(k):
    folder_name = "R" + str(i + 1)
    os.system("mkdir " + folder_name)
    os.system("cp TMP/reducer.py " + folder_name + "/reducer.py")

