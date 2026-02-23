def F(ret):
    if len(ret) == 1:
        novy = []
        novy.append(ret)
        return novy
    else:
        novy = F(ret[0:-1])
        if ret[-1] not in novy:
            novy.append(ret[-1])
        return novy
print(F('skuska'))