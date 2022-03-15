#Viết chương trình T(30,4)

import secrets

m = 30
n = 4

def primeGen():
    return 101
def T(c):
    p = primeGen()
    a = [secrets.randbelow(p) for i in range(n - 1)]
    keys = []
    for x in range(m):
        y = c
        for i in range(1, n - 1):
            y += a[i - 1] * pow(x, i)
        y = y % p
        if y < 0:
            y += p
        keys.append((x, y))
    return keys
        
print(encrypt(4))