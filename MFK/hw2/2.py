str = input()

def rev(n):
    print(str[n], end='')
    if n > 0:
        rev(n - 1)

rev(len(str) - 1)
print()