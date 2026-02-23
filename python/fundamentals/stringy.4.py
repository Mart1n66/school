def F(ret):
    posledne = 'a'
    for znak in ret:
        if znak > posledne:
            posledne = znak
    return posledne
print(F('aaxa'))