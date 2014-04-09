









case = 1

from random import randint

while case:
  case -= 1
  width = randint(20, 100)
  print width
  _sum = randint(20, 100)
  for i in xrange(_sum):
    print 'x' * randint(1, width),
  print '\n'


print 0
