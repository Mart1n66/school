def F(ret):
    if len(ret) == 1:
        if ret.isupper():
            return 1
        else:
            return 0
    else:
        if ret[-1].isupper():
            return F(ret[0:-1]) + 1
        else:
            return F(ret[0:-1]) + 0
print(F('aaAAAAa'))