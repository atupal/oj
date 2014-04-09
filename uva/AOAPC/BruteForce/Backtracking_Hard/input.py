
from random import randint
import sys

for _ in xrange(1):
    n = randint(10, 35)
    m = randint(1, n * n)
    m = 100 if m > 100 else m
    s = set()
    for i in xrange(m):
        s.add((randint(1,n), randint(1,n)))
    m = len(s)
    print n,m
    for i in s:
        print i[0],i[1]

print 0, 0
