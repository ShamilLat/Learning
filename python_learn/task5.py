def is_prime(x):
    for i in range(2, x):
        if x % i == 0:
            return False
    return True

def primes():
    num = 2
    while True:
        if is_prime(num):
            yield num
        num += 1