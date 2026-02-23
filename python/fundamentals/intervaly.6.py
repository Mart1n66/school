'''def F(t):
    for i in range(len(t)):
        je_obsiahnuty = True
        for j in range(len(t)):
            if i != j:
                if not (t[j][0] <= t[i][0] and t[i][1] <= t[j][1]):
                    je_obsiahnuty = False
                    break
        if je_obsiahnuty:
            return True
    return False'''
def F(t):
    for i in range(len(t)):
        pocet = 0
        for j in range(len(t)):
            if i != j:
                if t[j][0] <= t[i][0] and t[j][1] >= t[i][1]:
                    pocet +=1
        if pocet == len(t) - 1:
            return True
    return False

print(F( [[1,6],[2,5],[0,6]]))