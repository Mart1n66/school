def sucet_matic(A,B):
    if len(A) != len(B) or len(A[0]) != len(B[0]):
        print('neda sa scitat')
        return None
    vysledok = [[0]*len(A[0]) for _ in range(len(A))]
    print((vysledok))
    for i in range(len(A)):
        for j in range(len(A[0])):
            vysledok[i][j] = A[i][j] + B[i][j]
    return vysledok


print(sucet_matic([[1, 2], [3, 5]], [[5, 2], [-3, 4]]))