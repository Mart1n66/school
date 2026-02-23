def F(t,x):
    novy = []
    for prvok in t:
        if x > prvok[0] and x < prvok[1]:
            novy.append(prvok)
    return novy
print(F([[1,3],[1,5],[5,8],[1,6]],2))