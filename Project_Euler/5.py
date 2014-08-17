# -*- coding: utf-8 -*-
"""
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
"""
import operator
prime = [2,3,5,7,11,13,17,19]
cnt = [0] * len(prime)
for i in xrange(2,21):
  for j in xrange(len(prime)):
    t = i
    c = 0
    while t and t%prime[j]==0:
      c += 1
      t /= prime[j]
    cnt[j] = max(cnt[j], c)
ans=1
for i in xrange(len(prime)):
  ans*=prime[i]**cnt[i]
print ans
