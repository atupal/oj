# -*- coding: utf-8 -*-
"""
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
"""

"""
for i in xrange(0, 20):
  print i, (2**i)%10
1 2 4 8 6 2 4 8...
so the cicyle is 2, 4, 8, 6
"""

n = 15
ans = 0
r = [1, 2, 4, 8, 6]

def get(n):
  t = 2**n
  ret = 0
  while t:
    ret += t%10
    t /= 10
  return ret
print get(1000)
