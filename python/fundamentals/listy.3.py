def F(t):
    pocet = 0
    for prvok in t:
        pocet += 1
        for znak in prvok:
            if prvok.count(znak) > 1:
                pocet -= 1
                break
    return pocet


print(F(['bb', 'cc', 'aa', 'd', 'ab']))