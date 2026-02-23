def interval(a,b,c,d):
    if a <= c and b >= d or c <= a and d >= b:
        return True
    else:
        return False

print(interval(2,5,1,5))