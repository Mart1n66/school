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
    index = 0
    for i in range(len(zoznam_suctov)):
        if zoznam_suctov[i] > zoznam_suctov[index]:
            index = i
    return index'''
def F(A):
    sucet_max = 0
    index = 0
    for j in range(len(A[0])):
        sucet = 0
        for i in range(len(A)):
            sucet += A[i][j]
        if sucet > sucet_max:
            sucet_max = sucet
            index = j
    return index
print(F([[11, 4,6], [4, 6,50], [2, 6,10]]))