def interval(a,b,c,d):
    if a > d or b < c:
        return False
    else:
        return True
print(interval(1,3,4,5,))