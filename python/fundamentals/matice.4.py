'''def F(A,x):
    max = A[0][0]
    x,y = 0,0
    for i in range(0,len(A)-1):
        for j in range(0,len(A[i])-1):
            if A[i][j] > max:
                max = A[i][j]
                x,y = i,j

    return i,j'''
def F(A):
    max = A[0][0]
    index = [0,0]
    for i in range(len(A)):
        for j in range(len(A[i])):
            if A[i][j] > max:
                max = A[i][j]
                index[0] = i
                index[1] = j
    return index
print(F([[1,5],[11,3],[2,9]]))
