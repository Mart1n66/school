def F(n):
    if n == 1:
        ret = input()
        if len(ret) > 5:
            return 1
        else:
            return 0
    else:
        ret = input()
        if len(ret) > 5:
            return F(n-1) + 1
        else:
            return F(n - 1) + 0
print(F(5))