def F(n):
    t = []
    while True:
        cislo = int(input())
        if cislo in t:
            break
        t.append(cislo)
    return t
print(F(4))