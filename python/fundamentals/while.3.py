def F():
    cislo1 = int(input())
    cislo2 = int(input())
    pocet = 0
    if cislo1 == 0 or cislo2 == 0:
        return 0
    while True:
        cislo = int(input())
        if cislo > cislo1 + cislo2:
            pocet += 1
        cislo1 = cislo2
        cislo2 = cislo
        if cislo == 0:
            break
    return pocet
print(F())