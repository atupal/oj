
from random import randint
import sys

for _ in xrange(100):
    l = set()
    n = randint(4,21)
    k = randint(1,n * 4)
    print randint(1,n)
    for i in xrange(k):
        l.add((randint(1, n), randint(1, n)))
    for i in l:
        print i[0], i[1]
    print 0,0

