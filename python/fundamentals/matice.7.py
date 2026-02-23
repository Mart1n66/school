'''def F(A):
    stlpec = []
    rovnake = 0
    for j in range(len(A[0])):
        for i in range(len(A)):
            stlpec.append(A[i][j])
        for prvok in stlpec:
            if stlpec.count(prvok) == 1:
                rovnake += 1
            if rovnake == len(A):
                return True
        stlpec = []
    return False'''
def F(A):
    for j in range(len(A[0])):
        zoznam = []
        for i in range(len(A)):
            zoznam.append(A[i][j])
        for prvok in zoznam:
            if zoznam.count(prvok) > 1:
                return False
        return True
print(F([[2,4],[4,6],[2,6]]))