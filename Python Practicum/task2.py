def is_palindrome(x):
    x_f = x
    x_rev = 0
    while x > 0:
        x_rev = x_rev * 10 + x % 10
        x = x // 10
    if x_f == x_rev:
        return "YES"
    else:
        return "NO"
