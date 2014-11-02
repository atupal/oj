# -*- coding: utf-8 -*-
"""
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
"""
m = 600851475143
maxn = 775147

prime_list = list(xrange(maxn+4))

for i in xrange(2, maxn+1):
  if prime_list[i]:
    for j in xrange(i*2, maxn+1, i):
      prime_list[j] = 0

for i in prime_list[::-1]:
  if i and m%i==0:
    print i
    break
