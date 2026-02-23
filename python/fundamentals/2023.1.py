def F(t):
    novy = []
    while True:
        pocet = 0
        cislo = int(input())
        novy.append(cislo)
        for prvok in t:
            if t.count(prvok) <= novy.count(prvok):
                pocet += 1
        if pocet == len(t):
            break
    return cislo
print(F([6,2,2,1]))