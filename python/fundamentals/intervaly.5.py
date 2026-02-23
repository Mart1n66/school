def F(t):
    for i in range(len(t)):
        pocet = 0
        for j in range(len(t)):
            if i != j:
                if t[i][0] <= t[j][0] and t[i][1] >= t[j][1]:
                    pocet += 1
            if pocet == len(t) - 1:
                return True
    return False

print(F([[1, 2], [3, 5], [5, 6]]))