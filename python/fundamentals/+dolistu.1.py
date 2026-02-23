def F(n):
    t = []
    sucet = 0
    while True:
        cislo = int(input())
        t.append(cislo)
        sucet += cislo
        if sucet > n:
            break
    return t
print(F(10))