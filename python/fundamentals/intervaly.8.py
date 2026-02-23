'''def F(t):
    novy = []
    for i in range(len(t)):
        je_obsiahnuty = False
        for j in range(len(t)):
            if i != j:
                if (t[j][0] <= t[i][0] and t[i][1] <= t[j][1]):
                    je_obsiahnuty = True
        if je_obsiahnuty == False:
            novy.append(t[i])
    return novy'''
def F(t):
    novy = []
    for i in range(len(t)):
        pocet = 0
        for j in range(len(t)):
            if i != j:
                if not(t[j][0] <= t[i][0] and t[j][1] >= t[i][1]):
                    pocet += 1
        if pocet == len(t)-1:
            novy.append(t[i])
    return novy


print(F( [[1,2],[0,5],[6,7],[8,9],[2,3],[5,10]]))