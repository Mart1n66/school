def F(t):
    for i in range(len(t)):
        for j in range(len(t)):
            if i != j:
                if not (t[i][0] > t[j][1] or t[i][1] < t[j][0]):
                    return True
    return False

print(F( [[7,9],[0,4],[5,6]]))