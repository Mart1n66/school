def F():
    zoz = []
    ma = False
    x = 0
    while True:
        cislo = int(input())
        zoz.append(cislo)
        for i in zoz:
            if i in zoz and -i in zoz:
                x = abs(i)
        if x != 0:
            break
    return x
print(F())
