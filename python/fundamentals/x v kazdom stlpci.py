def F(A,x):
    pocet = 0
    for j in range(len(A[0])):
        for i in range(len(A)):
            if A[i][j] == x:
                pocet += 1
                break
    print(pocet)
    if pocet == len(A[0]):
        return True
    return False
print(F([[2,2],[2,4],[2,2]],2))