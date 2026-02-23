def F(zoznam):
    novy = ''
    for i in zoznam:
        novy += i[0]
    return novy
print(F(['bb', 'cc', 'aa', 'dd', 'aba']))