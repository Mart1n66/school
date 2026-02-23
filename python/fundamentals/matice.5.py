def F(A):
    pocet = 0
    pocet_nul = 0
    for j in range(len(A[0])):
        for i in range(len(A)):
            if A[i][j] == 0:
                pocet_nul += 1
            if pocet_nul == len(A):
                pocet += 1
        pocet_nul = 0
    return pocet

print(F([[1,0],[0,0],[0,1]]))