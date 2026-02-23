import copy

def stred(t):
    novy = copy.deepcopy(t)
    if len(novy) > 1:
        novy.pop(0)
        novy.pop(-1)
    else:
        print('prazdny zoznam')
        return None
    return novy

z = [5, [], 'a', [1, 2, 3], -5.5]
print(stred(z))
