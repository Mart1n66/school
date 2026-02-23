def F(A,x):
    max = A[0][0]
    for prvok in A:
        for cislo in prvok:
            if cislo > max:
                max = cislo
    return max
print(F([[1,5],[11,3],[2,9]],5))