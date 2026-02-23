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
    return(zoznam_prvocisel)

def rozloz_na_prvocisla(t):
    novy = []
    for i in range(len(t)):
        cislo = t[i]
        zoznam_prvocisel = faktorizacia(cislo)
        novy = novy + zoznam_prvocisel
        novy.append(0)
    return novy
print( rozloz_na_prvocisla( [14, 11, 18] ))