from __future__ import print_function

t = 10

print(t)

from random import randint, choice

for i in xrange(1, t+1):
  n = randint(10000, 10000)
  print(n)
  for x in xrange(n):
    print(choice(['G', 'H', 'S', 'R', '?']), end='')
  print()
