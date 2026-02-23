def F(A,x):
    pocet = 0
    for prvok in A:
        for cislo in prvok:
            if cislo == x:
                pocet += 1
    return pocet
print(F([[1,5],[5,3],[2,5]],5))