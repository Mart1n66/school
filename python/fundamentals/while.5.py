def F():
    ret = input()
    pocet = 1
    while True:
        ret2 = input()
        pocet += 1
        if ret[0] == ret2[0]:
            break
        ret = ret2
    return pocet
print(F())