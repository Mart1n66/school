def F(t):
    najvacsi = ''
    dlzka = 0
    for prvok in t:
        retazec_roznych = ''
        for znak in prvok:
            if znak not in retazec_roznych:
                retazec_roznych += znak
        if dlzka < len(retazec_roznych):
            najvacsi = prvok
            dlzka = len(retazec_roznych)
    return najvacsi

print(F(['bb', 'cc', 'aa', 'd', 'ab','aj','ackkk','akcd','ac']))