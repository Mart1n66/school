def maju_spolocny_prienik(lst):
  if len(lst) < 2:
    raise ValueError("Min. 2 intervaly su potrebne na urcenie prieniku.")
  prienik = [lst[0][0], lst[0][1]]
  for i in range(1, len(lst)):
    if prienik[0] > lst[i][1] or prienik[1] < lst[i][0]:
      return False
    prienik[0] = max(prienik[0], lst[i][0])
    prienik[1] = min(prienik[1], lst[i][1])
  return True


a = [[1, 15], [8, 20]]          # True
b = [[0, 4], [5, 9]]            # False
c = [[1, 15], [5, 8], [6, 20]]  # True
d = [[1, 5], [4, 8], [6, 20]]   # False

print(maju_spolocny_prienik(a))
print(maju_spolocny_prienik(b))
print(maju_spolocny_prienik(c))
print(maju_spolocny_prienik(d))
print(maju_spolocny_prienik( [[0,4],[2,5],[4,7]]))