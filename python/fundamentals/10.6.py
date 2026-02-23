def spolocny_prienik(intervaly):
    rozhodnutie = True
    if len(intervaly) < 2:
        raise ValueError
    for i in range(len(intervaly)-1):
        for j in range(1,len(intervaly[0])):
            if intervaly[i][0] >= intervaly[i+j][1] or intervaly[i][1] <= intervaly[i+j][0]:
                rozhodnutie = False
    return rozhodnutie

print( spolocny_prienik( [[0,4],[8,9],[4,7]] ))