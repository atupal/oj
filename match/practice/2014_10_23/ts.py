print 1
n = 5

from random import randint

p = []

maxn = 50
for i in xrange(n):
  r = randint(1, maxn)
  while r in p:
    r = randint(1, maxn)
  p.append(r)

def coprime(a, b):
  m = min(a, b)
  for i in xrange(2, m+1):
    if a % i == 0 and b % i == 0:
      return 0
  return 1

ans = 0
for x in xrange(n):
  for y in xrange(x+1, n):
    for z in xrange(y+1, n):
      i,j,k = p[x],p[y],p[z]
      if i != j and j != k and i!= k:
        a,b,c = coprime(i, j), coprime(j, k), coprime(i, k)
        if a and b and c:
          ans += 1
        if not a and not b and not c:
          ans += 1

print len(p)
for i in p:
  print i,
print 
print ans
