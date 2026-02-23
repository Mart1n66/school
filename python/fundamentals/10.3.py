def vyrez(z):
    if len(z) < 1:
        print('chyba')
        return None
    del z[-1]
    del z[0]
    print(z)

z = [5, [], 'a', [1, 2, 3], -5.5]
print(vyrez(z))
