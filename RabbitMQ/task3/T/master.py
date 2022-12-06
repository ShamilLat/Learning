import os
from sys import argv

txt_folder = argv[1]
# n = int(argv[2])
# k = int(argv[3])

with open("../input.txt", "r") as f:
    n = int(f.readline())
    k = int(f.readline())

# разбрасывает текстовые файлы по Mn папкам
for i in range(n):
    os.system("cp " + txt_folder + "/" + str(i + 1) + ".txt " + txt_folder + "/../M" + str(i + 1) + "/text.txt")

for i in range(n):
    os.system("python3 ../M" + str(i + 1) + "/splitter.py " + str(i + 1))