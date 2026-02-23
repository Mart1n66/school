def F():
    cislo1 = int(input())
    cislo2 = int(input())
    pocet = 0
    while True:
        cislo3 = int(input())
        if cislo2 > cislo3 and cislo2 > cislo1:
            pocet += 1
        cislo1 = cislo2
        cislo2 = cislo3
        if cislo3 == 0:
            break
    return pocet
print(F())