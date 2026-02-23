def F(n):
    t = []
    cislo = int(input())
    min = cislo
    max = cislo
    t.append(cislo)
    while True:
        cislo = int(input())
        t.append(cislo)
        if cislo > max:
            max = cislo
        if cislo < min:
            min = cislo
        if max - min > n:
            break
    return t
print(F(6))