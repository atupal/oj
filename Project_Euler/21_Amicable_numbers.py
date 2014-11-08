# -*- coding: utf-8 -*-
"""
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
"""
import math

def getsum(x):
  ret = 1
  for i in xrange(2, int(math.sqrt(x))+1):
    if x%i == 0 and i!=x:
      if i < x/i:
        ret += i + x/i
      elif i*i == x:
        ret += i
  return ret

ans = 0
for i in xrange(1, 10001):
  t = getsum(i)
  if t != i and getsum(t) == i:
    ans += i+t

print ans/2
