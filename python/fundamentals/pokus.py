def determinant(A):
    # determinant vypocitame podla rozvoja podla prveho riadku
    # determinant sa klasicky pocita priam ukazkovo rekurzivne
    # base-case, ak je matica rozmerov 1x1
    if len(A) == 1:
        return A[0][0]
    else:
        # rozvoj podla prveho riadku a i-teho prvku, i ide od 0 po pocet_stlpcov-1
        vysledok = 0
        for i in range(len(A[0])):

            # vypocitaj maticu, ktora vznikne odstranenim prveho riadku a i-teho stlpca!
            # tuto maticu oznacime ako B
            B = []
            for riadok in range(1, len(A)):  # premenna riadok ide od 1, cim vynechame prvy riadok matice A
                B_riadok = []
                for stlpec in range(len(A[0])):
                    if stlpec != i:  # ak sa stlpec rovna i, to znamena, ze dany stlpec chceme vynechat!
                        B_riadok.append(A[riadok][stlpec])
                B.append(B_riadok)

            # vezmeme prvok A[0][i] a pripocitame/odpocitame podla parity i hodnotu A[0][i]*determinant(B)
            if (i % 2 == 0):
                vysledok += A[0][i] * determinant(B)
            else:
                vysledok -= A[0][i] * determinant(B)
        return vysledok
print(determinant([[1,2,3],[4,5,6],[7,8,10]]))