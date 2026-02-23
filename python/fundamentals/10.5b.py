def sucin_matic(A,B):
    if len(A[0]) != len(B):
        print('nie je mozne nasobit')
        return None
    vysledok = []
    riadok = []
    for i in range(len((A))):
        for j in range(len(B[0])):
            riadok.append(0)
        vysledok.append(riadok)
        riadok = []
    for i in range(len(vysledok)):
        for j in range(len(vysledok[0])):
            sucet = 0
            for k in range(len(A[0])):
                sucet += A[i][k] * B[k][j]
            vysledok[i][j] = sucet
    return vysledok

print(sucin_matic([[1, 2], [3, 5], [-2, -1]], [[2], [-2]]))
print(sucin_matic([[1, 2], [3, 5]], [[5, 2], [-3, 4]]))
