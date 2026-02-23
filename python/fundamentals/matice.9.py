'''def F(A):
    stlpec = []
    sucet = 0
    zoznam_suctov = []
    for j in range(len(A[0])):
        for i in range(len(A)):
            stlpec.append(A[i][j])
        for prvok in stlpec:
            sucet += prvok
        zoznam_suctov.append(sucet)
        stlpec = []
        sucet = 0
    for prvok in zoznam_suctov:
        if zoznam_suctov.count(prvok) > 1:
            return True
    return False'''
def F(A):
    zoznam = []
    for j in range(len(A[0])):
        sucet = 0
        for i in range(len(A)):
            sucet += A[i][j]
        zoznam.append(sucet)
    for i in zoznam:
        if zoznam.count(i) > 1:
            return True
    return False
print(F([[10, 8], [4, 6], [6, 6]]))