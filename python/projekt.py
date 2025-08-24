import random
def generovanie_hracieho_pola(n): #funkcia na vygenerovanie zoznamu rozmeru nxn len s pouzitim znakov +,*,.
    zoznam = []
    for i in range(n):
        riadok = []
        for j in range(n):
            if i == j == 0:
                riadok.append('+')
            elif n % 2 == 1 and i == j == n - 1:
                riadok.append('*')
            elif n % 2 == 0 and i == n - 1 and j == 0:
                riadok.append('*')
            else:
                riadok.append('.')
        zoznam.append(riadok)
    vkladanie_teleportov(zoznam, n) #nasledne nahodne vlozenie teleportov(na rozne riadky) oznacenych pismenamy abecedy
    return zoznam #funckia vrati zoznam uz aj s nahodne rozmiestnenymi teleportami

def vkladanie_teleportov(zoznam, n):
    pocet_teleportov = n//2
    suradnice = []
    for i in range(n):
        for j in range(n):
            if zoznam[i][j] == '.':
                suradnice.append((i, j)) #vytvorenie zoznamu s dostupnymi suradnicami kde mozu byt vkladane teleporty

    i = 0
    while i < pocet_teleportov:
        nahodny_prvok = random.randint(0, len(suradnice) - 1)
        x, y = suradnice[nahodny_prvok]
        suradnice.pop(nahodny_prvok) #vyber nahodneho prvku zo zoznamu volnych suradnic a jeho nasledne odstranenie z toho zoznamu
        while True:
            nahodny_prvok = random.randint(0, len(suradnice) - 1)
            x2, y2 = suradnice[nahodny_prvok] #vyber druheho nahodneho prvku zoznamu
            if x2 != x: #overenie ci dany prvok je na inom riadku, ak podmienka sedi breaknutie cyklu a ulozenie znakov do zoznamu, ktory bol vygenerovany v prvej funkcii
                suradnice.pop(nahodny_prvok)
                break
        zoznam[x][y] = chr(65 + i)
        zoznam[x2][y2] = chr(65 + i)

        nahodny_prvok = random.randint(0, len(suradnice) - 1)
        x, y = suradnice[nahodny_prvok]
        suradnice.pop(nahodny_prvok)
        while True:
            nahodny_prvok = random.randint(0, len(suradnice) - 1)
            x2, y2 = suradnice[nahodny_prvok]
            if x2 != x:
                suradnice.pop(nahodny_prvok)
                break
        zoznam[x][y] = chr(97 + i)
        zoznam[x2][y2] = chr(97 + i) #zopakovanie to iste aj pre negativny teleport a priradenie znaku na prislusne suradnice zoznamu z prvej funkcie
        i += 1
def tah_kockou():
    sucet = 0
    while True:
        hod_kockou = random.randint(1,6)
        sucet += hod_kockou
        if hod_kockou != 6:
            break
    return sucet #funkcia na hod kockou ktora scituje body v pripade ze hrac hodi 6ku

def suradnice_vstupu_a_vystupu(zoznam,symbol): #funkcia, ktora v pripade, ze hrac stoji na teleporte vrati suradnice daneho teleportu v podobe zoznamu kde prvy prvok zoznamu je vstup a druhy prvok je vystup teleportu
    vyskyt = 0
    suradnice_vystupu = []
    suradnice_vstupu = []
    suradnice_spolu = []
    if symbol == 1 or symbol == 2 or symbol == 3 or symbol == 4:
        return suradnice_spolu
    for i in range(len(zoznam)):
        for j in range(len(zoznam[i])):
            if (ord(symbol) > 64 and ord(symbol) < 91) or (ord(symbol) > 96 and ord(symbol) < 123):
                if zoznam[i][j] == symbol:
                    vyskyt += 1
                    if vyskyt == 1:
                        suradnice_vstupu.append((i,j))
                    elif vyskyt == 2:
                        suradnice_vystupu.append((i,j))
                        suradnice_spolu = suradnice_vstupu + suradnice_vystupu
                        return suradnice_spolu
    return suradnice_spolu

def vypis_pola(zoznam, n, k, zoznam_hracov, cislo_hraca):
    print('Hracie pole:') #funckia, ktora vypisuje hracie pole po tahu kazdeho hraca
    print('  ', end='')
    for i in range(n):
        print(i, end=' ')
    print()
    for i in range(n):
        print(i, end=' ')
        for j in range(n):
            hrac_na_suradnici = None
            for l in range(len(zoznam_hracov)): # v pripade, ze sa suradnice, ktore ide vypisat rovnaju so suradnicami niektoreho hraca vypise cislo hraca namiesto prislusneho znaku zoznamu
                sur_x, sur_y = zoznam_hracov[l]
                if sur_x == i and sur_y == j:
                    hrac_na_suradnici = l+1
                    break
            if hrac_na_suradnici != None:
                print(hrac_na_suradnici,end=' ')
            else:
                print(zoznam[i][j],end=' ')
        print()
    for i in range(2*n +1):
        print('=',end='')
    print()

def pocet_krokov_do_vzdialenosti(zoznam_hracov,n,i):
    if zoznam_hracov[i][0] % 2 == 0: #funkcia na vypocet moznych krokov do ciela pre pripad, ze hrac hodi viac aby sa nepohol
        riadok = n - 1 - zoznam_hracov[i][1]
    else:
        riadok = zoznam_hracov[i][1]
    stlpec = n * (n - 1 - zoznam_hracov[i][0])
    return riadok+stlpec

def hra(zoznam,n,k): #funkcia simulujuca priebeh hry pre k hracov
    zoznam_hracov = []
    for i in range(k): # vytvorenie zoznamu s k-prvkami tak, ze kazdy prvok bude mat dve hodnoty teda suradnice pre kazdeho s hracov
        zoznam_hracov.append([0,0])
    pocet_moznych_krokov = []
    for i in range(k):
        pocet_moznych_krokov.append(n**2-1)
    vypis_pola(zoznam, n, k,zoznam_hracov,i)
    if n % 2 == 0:
        ciel = [n - 1, 0]
    else:
        ciel = [n - 1, n - 1] #zistenie kde sa nachadza ciel podla parity zadaneho parametra n
    while True:

        for i in range(k):
            print('Pozicie hracov:')
            for j in range(k):
                print('Hrac c.', j + 1, zoznam_hracov[j])
            print('---')
            hodene_cislo = tah_kockou()
            if hodene_cislo > pocet_moznych_krokov[i]: #v  pripade, ze hrac hodil vacsie cislo ako ma do ciela krokov vypise, ze hodil viac a preskoci na tah dalsieho hraca
                print('hrac c.', i + 1, 'hodil spolu na kocke:', hodene_cislo, 'bodov')
                print('hrac c.',i + 1, 'hodil viac bodov nez je vzdialenost do ciela!')
                vypis_pola(zoznam, n, k,zoznam_hracov,i)
                continue
            print('hrac c.', i + 1, 'hodil spolu na kocke:', hodene_cislo, 'bodov')
            for j in range(hodene_cislo): #v pripade, ze hrac hodil cislo, o ktore sa mozu posunut tak ho to posunie podla toho riadku, v ktorom sa nachadza bud doprava alebo dolava
                if zoznam_hracov[i][0] % 2 == 0:
                    zoznam_hracov[i][1] += 1
                    if zoznam_hracov[i][1] >= n:
                        zoznam_hracov[i][1] = n - 1
                        zoznam_hracov[i][0] += 1
                else:
                    zoznam_hracov[i][1] -= 1
                    if zoznam_hracov[i][1] < 0:
                        zoznam_hracov[i][1] = 0
                        zoznam_hracov[i][0] += 1
            aktualny_riadok, aktualny_stlpec = zoznam_hracov[i]
            symbol = zoznam[aktualny_riadok][aktualny_stlpec] #ulozenie symbolu, na ktorom stoji hrac
            aktualny_riadok, aktualny_stlpec = ([], [])
            vstup_vystup = suradnice_vstupu_a_vystupu(zoznam, symbol) #ulozenie suradnic ak hrac stoji na teleporte
            print('hrac c.', i + 1, 'sa posuva na policko:', zoznam_hracov[i])
            if len(vstup_vystup) > 0: #podmienka, ktora sa vykona len ak hrac stoji na teleporte
                if ord(symbol) > 64 and ord(symbol) < 91: #v pripade, ze hrac stoji na vstupe pozitivneho teleportu tak ho to presunie na vystup a vypise, ze kam
                    if zoznam_hracov[i][0] == vstup_vystup[0][0] and zoznam_hracov[i][1] == vstup_vystup[0][1]:
                        zoznam_hracov[i][0],zoznam_hracov[i][1] = vstup_vystup[1]
                        print('hrac c.', i + 1, 'sa cez pozitivny teleport posuva na policko:', zoznam_hracov[i])
                elif ord(symbol) > 96 and ord(symbol) < 123: #v pripade, ze hrac stoji na vstupe negativneho teleportu tak ho to presunie na vystup a vypise, ze kam
                    if zoznam_hracov[i][0] == vstup_vystup[1][0] and zoznam_hracov[i][1] == vstup_vystup[1][1]:
                        zoznam_hracov[i][0],zoznam_hracov[i][1] = vstup_vystup[0]
                        print('hrac c.', i + 1, 'sa cez negativny teleport posuva na policko:', zoznam_hracov[i])
            pocet_moznych_krokov[i] = pocet_krokov_do_vzdialenosti(zoznam_hracov,n,i) #ulozenie poctu moznych pre daneho hraca, ktory je na tahu
            vypis_pola(zoznam, n, k,zoznam_hracov,i)
            if zoznam_hracov[i] == ciel: #kontrola ci sa dany hrac nedostal do ciela
                print('hrac c.', i + 1, 'vyhral!')
                return

n = int(input('Zadaj parameter n (velkost hracieho pola):'))
k = int(input('Zadaj parameter k (pocet hracov):'))
if n < 5 or n > 10 or k < 1 or k > 4:  # osetrenie parametrov zadanych uzivatelom
    raise ValueError

hra(generovanie_hracieho_pola(n),n,k)