# -*- coding: utf-8 -*-
"""
Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.


How many such routes are there through a 20×20 grid?
"""

maxn = 20

dp = []
for i in xrange(maxn+1):
  dp.append([-1]*(maxn+1))

for i in xrange(maxn+1):
  dp[i][0] = dp[0][i] = 1

for i in xrange(1, maxn+1):
  for j in xrange(1, maxn+1):
    dp[i][j] = dp[i-1][j] + dp[i][j-1]

print dp[20][20]
