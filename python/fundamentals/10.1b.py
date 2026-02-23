def najcastejsie():
  zadane_cisla = []
  cislo = None
  najcastejsie = cislo
  while cislo != 0:
    cislo = int(input("Zadaj cislo: "))
    zadane_cisla.append(cislo)
    if zadane_cisla.count(cislo) > zadane_cisla.count(najcastejsie):
      najcastejsie = cislo
  return najcastejsie

print(najcastejsie())