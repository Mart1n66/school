def F(n):
    t = []
    zoznam_roznych = []
    while True:
        cislo = int(input())
        t.append(cislo)
        if cislo not in zoznam_roznych:
            zoznam_roznych.append(cislo)
        if len(zoznam_roznych) == n:
            break
    return t
print(F(3))
