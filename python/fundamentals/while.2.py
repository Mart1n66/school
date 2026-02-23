def F():
    pocet = 0
    prve = int(input())
    if prve == 0:
        return 0
    pocet_zasebou = 1
    while True:
        cislo = int(input())
        if prve == cislo:
            pocet_zasebou += 1
        if prve != cislo and pocet_zasebou > 1:
            pocet += 1
            pocet_zasebou = 1
        prve = cislo
        if cislo == 0:
            break
    return pocet
print(F())

