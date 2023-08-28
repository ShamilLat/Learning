import os

path = "M1"
i = 1
while (os.path.exists(path)):
    os.system("rm -R " + path)
    os.system("rm Txt/" + str(i) + ".txt")
    i += 1
    path = "M" + str(i)

path = "R1"
i = 1
while (os.path.exists(path)):
    os.system("rm -R " + path)
    i += 1
    path = "R" + str(i)
