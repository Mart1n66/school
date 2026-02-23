def F(t,x):
    for prvok in t:
        if x > prvok[0] and x < prvok[1]:
            return prvok
print(F([ [5, 8],[1,5]], 2))