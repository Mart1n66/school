def ma_duplikat(t):
    for i in t:
        if t.count(i) > 1:
            return True
    return False

a = [1, 2, [], 3,[], 'a']
print(ma_duplikat(a))