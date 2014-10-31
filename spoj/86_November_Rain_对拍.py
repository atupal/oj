
n = 100

maxn = 1000

ret = []

from random import randint
print 1
print n


def area(A, B, C):
  AB = (B[0] - A[0], B[1] - A[1])
  AC = (C[0] - A[0], C[1] - A[1])
  return AB[0] * AC[1] - AB[1] * AC[0]

def cross(a ,b):
  return ( area( (a[0], a[1]) , (a[2], a[3]), (b[0], b[1])) * \
    area( (a[0], a[1]) , (a[2], a[3]), (b[2], b[3])) < 0 \
    and area( (b[0], b[1]) , (b[2], b[3]), (a[0], a[1])) * \
    area( (b[0], b[1]) , (b[2], b[3]), (a[2], a[3])) < 0 )



for i in xrange(n):
  while 1:
    x1 = randint(1, maxn)
    x2 = randint(x1+1, maxn+1)
    y1 = randint(1, maxn)
    y2 = randint(1, maxn)
    while y2 == y1:
      y2 = randint(1, maxn)

    flag = 1
    for seg in ret:
      if cross(seg, (x1, y1, x2, y2)):
        flag = 0
        break

    if flag:
      ret.append((x1, y1, x2, y2))
      break

for seg in ret:
  print seg[0], seg[1], seg[2], seg[3]
