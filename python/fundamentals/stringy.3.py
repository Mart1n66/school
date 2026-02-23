def F(ret):
    ret2 = ''
    for znak in ret:
        if znak in ret2:
            return True
        ret2 += znak
    return False
print(F('abbc'))