str = input()
symbols = ['-', ')', '(', ' ']
for i in symbols:
    str = str.replace(i, '')

print(str)