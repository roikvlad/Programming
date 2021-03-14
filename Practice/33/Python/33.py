_print = print

def create(a, b = 0, c = 0):
    d = []
    for j in range(0, a):
        d.append(b)
        b = b + c
    return d

def sortirovka(d, a):
    buff = 0
    i = 1
    while i < a:
        buff = d[i]
        j = i - 1
        while j >= 0 and d[j] > buff:
            d[j + 1] = d[j]
            j = j - 1
        d[j + 1] = buff
        i = i + 1
    return d

def print(d):
    _print(d)
    return 0;


a = int(input())
b = int(input())
c = int(input())

d = create(a, b, c)
d = sortirovka(d, a)

print(d)

