


from random import randint, choice, shuffle

n = randint(10, 300)
m = randint(n/2, n)
m = n
m1 = randint(m/2, m)
m2 = m - m1
print n,m
 
c = [1] * m1 + [2] * m2
shuffle(c)

for i in c:
  print i,
  if i == 1:
    print randint(1, n/3+1)
  else:
    a = randint(1, n-1)
    print a, randint(1, n-a)
