
a,b = map(int, raw_input().split())
a, b = max(a, b), min(a, b)

for i in xrange(1, a*a+b*b+1):
  if i*i == a*a + b*b or b*b+i*i==a*a:
    print 'YES'
    exit(0)

print "NO"
