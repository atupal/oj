
l, s1, s2 = map(float, raw_input().split())

s = max(s1, s2) - min(s1, s2)

q = int(raw_input())

import math

M = 1.4142135623730951

for i in xrange(q):
  x = float(raw_input())
  print '%.4f' % ( (l - math.sqrt(x)) * M / s )
