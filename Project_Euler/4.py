# -*- coding: utf-8 -*-
"""
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
"""
a = sorted([i*j for i in xrange(100,1000) for j in xrange(100,1000)])
for i in map(str, a[::-1]):
  if all(map(lambda x:i[x]==i[len(i)-1-x], list(xrange(len(i)/2)))):
    print i
    break
