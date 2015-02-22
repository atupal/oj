# -*- coding: utf-8 -*-

import math

t = int(raw_input())

def solve():
  n = int(raw_input())
  A = map( int, raw_input().split() )
  A = set(A)

  cnt = 0
  while 1:
    R = []
    for a in A:
      if int(math.sqrt(a)) ** 2 == a:
        R.append(a)

    for r in R:
      A.remove(r)

    if not A:
      break

    cnt += 1

    N = set()
    for i in A:
      for j in A:
        if i != j:
          N.add(i*j)

    A = N

  print 2**cnt

for _ in xrange(t):
  solve()
