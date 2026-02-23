def najcastejsie():
  zadane_cisla = []
  najcastejsie = 0
  while True:
    cislo = int(input())
    if cislo == 0:
        break
    zadane_cisla.append(cislo)
    if zadane_cisla.count(cislo) > zadane_cisla.count(najcastejsie):
      najcastejsie = cislo
  return najcastejsie

print(najcastejsie())