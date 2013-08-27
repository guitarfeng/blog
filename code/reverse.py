
def reverse(n):
    if n < 0:
        n = 0 - n

    r = 0
    while n != 0:
        r = r * 10 + (n % 10)
        n /= 10

    return r

print reverse(54779)
