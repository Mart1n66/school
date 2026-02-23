def F(ret,x):
    if len(ret) == 1:
        if ret == x:
            return 1
        else:
            return 0
    else:
        if ret[-1] == x:
            return F(ret[0:-1],x) + 1
        else:
            return F(ret[0:-1],x) + 0
print(F('axnaxax','x'))