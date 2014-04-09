









case = 100

from random import randint

while case:
  case -= 1
  width = randint(20, 50)
  print width
  _sum = randint(10, 40)
  for i in xrange(_sum):
    print 'x' * randint(1, width/2),
  print '\n'

case = 100
while case:
  case -= 1
  width = randint(20, 50)
  print width
  _sum = randint(10, 40)
  for i in xrange(_sum):
    print 'x' * randint(1, width/2),
  print '\n'


print 0
