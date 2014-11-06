

a, b, c = map(int, raw_input().split())

if a < b:
  d = (c+a-1)/a
  low = 0 
  high = 1000000000

  while low < high:
    mid = (low+high) >> 1
    if mid==0:
      break
    q = d/mid
    r = d%mid

    s = min( b,  q*a)  * (mid-r)
    s += min(b, (q+1)*a) * r
    if s < c:
      low = mid+1
    else:
      high = mid

  c = high
else:
  d = (c+b-1)/b
  c = d

print d, c
