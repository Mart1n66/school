def  usporiadaj_trojice(t):
    novy = []
    prechodny = []
    for i in range(0,len(t),3):
        prechodny.append(t[i])
        prechodny.append(t[i+1])
        prechodny.append(t[i+2])
        prechodny.sort()
        novy = novy + prechodny
        prechodny = []
    return novy

print( usporiadaj_trojice( [5, 9, -10, 0, 2, 0, 4, -1, 10] ))