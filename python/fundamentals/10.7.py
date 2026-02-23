from random import randint

def birthday_paradox(subjects, iterations):
    coincidence_count = 0
    for _ in range(iterations):
        sample = set()  # Použijeme množinu na kontrolu duplicity
        for _ in range(subjects):
            bday = get_bday()
            if bday in sample:  # Ak dátum už existuje, máme zhodu
                coincidence_count += 1
                break
            sample.add(bday)
    return coincidence_count / iterations

def get_bday():
    month = randint(1, 12)
    if month in {1, 3, 5, 7, 8, 10, 12}:
        return (randint(1, 31), month)
    elif month == 2:
        return (randint(1, 29 if randint(1, 4) == 1 else 28), month)  # Šanca na 29 dní
    else:
        return (randint(1, 30), month)

pravdepodobnost = birthday_paradox(23, 10000)
print(f"Pravdepodobnosť ľudí s rovnakým dátumom narodenia: {pravdepodobnost * 100:.2f}%")

