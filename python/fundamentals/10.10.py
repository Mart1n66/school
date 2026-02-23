def delitelnost(a, d):
    return a % d == 0

def faktorizacia(n):
    zoznam_prvocisel = []
    a = 2
    while n > 1:
        if delitelnost(n,a):
            zoznam_prvocisel.append(a)
            n = n/a
        else:
            a += 1
    return zoznam_prvocisel
print(faktorizacia(11))