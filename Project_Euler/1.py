ans = 0
for i in xrange(1, 1000):
  if i % 3 == 0 or i % 5 == 0:
    ans += i
print ans
