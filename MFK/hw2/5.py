str = input()

str = str[str.find(' ') + 1:] + ' ' +  str[:str.find(' ')]
print(str)