def F(ret):
    if len(ret) <= 1:
        return True
    else:
        if ret[0] != ret[-1]:
            return False
        return F(ret[1:-1])
print(F('aanna'))