from hexlet import pairs
import json


ones = [1, 1, 1, 1, 1]

tmp = {"aaa": [1, 1, 1, 1, 1], "bb": 5}
b = json.dumps(tmp)

keys = list(tmp.keys())
val = list(tmp.values())
pair = list(tmp.items())

print(pair)
print()

for ff in pair:
    print(ff)
    b = json.dumps(ff)
    print(b)
    c = json.loads(b)
    print("c", c)
    print("c[1]", c[1])
    # print(sum(c[1]))
    print()



    
# print(b)

# print(list)