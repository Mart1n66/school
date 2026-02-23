def F(ret,x):
    if len(ret) == 1:
        if ret == x:
            return True
        else:
            return False
    else:
        if ret[-1] == x:
            return True
        else:
            return F(ret[0:-1],x)
print(F('nrefjkgxghoeg','x'))