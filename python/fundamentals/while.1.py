def F(k):
    prve = int(input())
    pocet = 1
    while True:
        cislo = int(input())
        if prve == cislo:
            pocet +=1
        else:
            prve = cislo
            pocet = 1
        if pocet == k:
            break
    return cislo
print(F(3))