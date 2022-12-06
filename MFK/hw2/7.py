str = input()
new_str = ''

for i in str:
    if i.isalpha():
        new_str = new_str + chr(ord(i) + 1)
    else:
        new_str = new_str + i

print(new_str)