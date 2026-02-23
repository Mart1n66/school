'''def F(A):
    for j in range(len(A[0])):
        i = 0
        cislo = A[i][j]
        while i < len(A):
            if A[i][j] == cislo:
                i += 1
            else:
                break
            if i == len(A):
                return True
    return False'''
def F(A):

    for j in range(len(A[0])):
        pocet = 1
        prve = A[0][j]
        for i in range(1,len(A)):
            if A[i][j] == prve:
                pocet += 1
        if pocet == len(A):
            return True
    return False

print(F([[1,0],[0,0],[0,1]]))
print(F([[1,5],[1,5],[5,5]]))
print(F([[1,3],[1,4],[5,5]]))
print(F([[1,5],[1,4],[1,5]]))
