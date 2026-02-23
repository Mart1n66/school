def F(ret1,ret2):
    rozhodnutie = True
    for znak in ret1:
        if znak not in ret2:
            rozhodnutie = False
    return rozhodnutie
print(F('abc','abeceda'))