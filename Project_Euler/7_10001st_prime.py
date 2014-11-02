# -*- coding: utf-8 -*-
"""
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?
"""
maxn = 105000
prime_list = [1] * (maxn+4)
prime_list[0], prime_list[1] = 0, 0

for i in xrange(2, maxn+1):
  if prime_list[i]:
    for j in xrange(i*2, maxn+1, i):
      prime_list[j] = 0

cnt=0
for i in xrange(maxn):
  cnt += prime_list[i]
  if cnt == 10001:
    print i
    break
