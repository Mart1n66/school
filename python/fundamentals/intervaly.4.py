def F(t):
    nema_prienik = True
    for i in range(len(t)):
        for j in range(len(t)):
            if i != j:
                if not(t[i][0] > t[j][1] or t[i][1] < t[j][0]):
                    nema_prienik = False
        if nema_prienik:
            return True
    return False

print(F([[1,2],[3,5],[4,6]]))