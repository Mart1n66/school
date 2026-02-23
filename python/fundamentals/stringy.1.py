'''def F(ret1,ret2):
    rozhodnutie = False
    for znak in ret1:
        if znak in ret2:
            rozhodnutie = True
    return rozhodnutie'''
def F(ret1,ret2):
    for znak in ret1:
        if znak in ret2:
            return True
    return False
print(F('abc','abe'))
