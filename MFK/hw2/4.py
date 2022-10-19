str = input()
print(str[str.find('"') + 1:str.find('"', str.find('"') + 1)])