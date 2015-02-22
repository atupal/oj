# -*- coding: utf-8 -*-

# ans is 2^( 2^n - n)
#def get(x):
#  cnt = 0
#  n = 2**x
#  for i in xrange( 2**n ):
#    s = 0
#    for j in xrange(n):
#      if (i>>j)&1:
#        s ^= j
#
#    if s == 0:
#      cnt += 1
#
#  return cnt
#
#for i in xrange(1, 10):
#  print i, get(i)

def get(n):
  return 2**(2**n - n) % MOD

MOD = 10**9+7
def exp(n, m):
  base = 2
  ret = 1
  while n:
    if n%2==1:
      ret *= base
      ret %= m
    base *= base
    base %= m
    n /= 2

  return ret

t = int(raw_input())
for i in xrange(t):
  n = int(raw_input())
  ret = (exp(n, MOD-1)-n%(MOD-1)+MOD-1)%(MOD-1)
  print exp(ret, MOD)

