def F(A,x):
    for prvok in A:
        if x in prvok:
            return True
    return False
print(F([[1,5],[5,3],[2,2]],7))