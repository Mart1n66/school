def F(n):
    if n == 1:
        return 1
    else:
        if n % 2 == 0:
            return F(n-1) - n
        else:
            return F(n-1) + n

print(F(6))