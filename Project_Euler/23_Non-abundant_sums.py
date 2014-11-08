"""
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
A number 
 is called deficient if the sum of its proper divisors is less than 
 and it is called abundant if this sum exceeds 
.
As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.
Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
"""

import math

d = {}
a = []

def get(x):
  s = 0
  u = int(math.sqrt(x+1))
  for i in xrange(2, u+1):
    if x%i == 0:
      if i*i != x:
        s += i + x/i
      else:
        s += i
  
  if s > x:
    a.append(x)
    d[x] = 1
  else:
    d[x] = 0

ans = 1
for i in xrange(2, 28124):
  ans += i
  get(i-1)
  for t in a:
    if d[i-t]:
      ans -= i
      break

print ans
