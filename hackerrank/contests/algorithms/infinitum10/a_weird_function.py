#!/bin/sh
# -*- coding: utf-8 -*-
''''which python2 >/dev/null && exec python2 "$0" "$@" # '''
''''which python  >/dev/null && exec python  "$0" "$@" # '''

def __gcd(a, b):
  a, b = max(a, b), min(a, b)
  return a if b==0 else __gcd(b, a%b)

def function(L,R):
  sum=0
  for i in range(L,R+1):              #[L,R]
    for j in range(1,i+1):          #[1,i]
      cnt=0
      if (j)*(j+1) == 2*i :
        for k in range(1,i+1):  #[1,i]
          if __gcd(k,i)==1:   #__gcd Greatest Common Divisor 
            cnt+=1
      sum=sum+cnt
  return sum

import math
def v1(L, R):
  sum=0
  for j in xrange(1, 10**6+1):
    i = j*(j+1)/2
    if i >= L and i <= R:
      for k in xrange(1, i+1):
        if __gcd(k, i) == 1:
          sum += 1

  return sum


for i in xrange(1, 50):
  print function(1, i), v1(1, i)
