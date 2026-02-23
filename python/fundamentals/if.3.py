def interval(a,b,x):
    if abs(x-a) < abs(x-b):
        return a
    else:
        return b
print(interval(2,1,4))