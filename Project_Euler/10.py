# -*- coding: utf-8 -*-
"""
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
"""
maxn = 2000000
prime_list = list(xrange(maxn+1))
prime_list[1]=0

for i in xrange(2, maxn+1):
  if prime_list[i]:
    for j in xrange(i*2, maxn+1, i):
      prime_list[j] = 0

print sum(prime_list)
