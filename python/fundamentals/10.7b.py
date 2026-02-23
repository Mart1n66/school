from random import randint, choice

def birthday_paradox(subjects, iterations):
  coincidence_count = 0
  for i in range(iterations):
    sample = [get_bday() for _ in range(subjects)]
    is_same_date = len(sample) != len(set(sample))
    if is_same_date:
      coincidence_count += 1
  return coincidence_count / iterations

def get_bday():
  day, month = None, randint(1, 12)
  if month in (1, 3, 5, 7, 8, 10, 12):
    day = randint(1, 31)
  elif month == 2:
    day = randint(1, choice([28, 28, 28, 29]))
  else:
    day = randint(1, 30)
  return (day, month)

pravdepodobnost = birthday_paradox(23, 10000)
print(f"Pravdepodobnost ludi s rovnakym datumom nar. {pravdepodobnost * 100}%")