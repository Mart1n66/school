def F(n):
    if n == 1:
        retazec = input()
        return retazec
    else:
        retazec2 = input()
        retazec_predosli = F(n-1)
        if len(retazec2) >= len(retazec_predosli):
            return retazec2
        else:
            return retazec_predosli

print(F(3))