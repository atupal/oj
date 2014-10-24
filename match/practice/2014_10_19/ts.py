
print 5
n = 100
m = 1000

from random import randint
for i in xrange(5):
  print n
  for i in xrange(n):
    for j in xrange(n):
      print randint(1, 1000000000),
    print
  print m
  for i in xrange(m):
    print randint(1, n), randint(1, n), randint(1, n) * 2 + 1
