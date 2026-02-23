def F(t,x):
    pocet = 0
    for prvok in t:
        if x > prvok[0] and x < prvok[1]:
            pocet += 1
    return pocet
print(F([[1,3],[1,5],[5,8],[1,6]],2))