def F(A):
    for j in range(len(A[0])):
        min = A[0][j]
        for i in range(len(A)):
            if A[i][j] < min:
                min = A[i][j]
        for i in range(len(A)):
            if A[i][j] == min:
                A[i][j] = 0
    return A
print(F([[-2,1],[1,1],[0,1],[4,1]]) )