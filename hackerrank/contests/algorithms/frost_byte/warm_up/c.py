
n = int(raw_input())

s = map(int, raw_input())

a = set()

for i in xrange(len(s)):
  for j in xrange(9):
    t = []
    for x in s[i:]:
      t.append( str( (x+j)%10 ) )
    for x in s[:i]:
      t.append( str( (x+j)%10 ) )
    a.add(''.join(t))

print min(a)
