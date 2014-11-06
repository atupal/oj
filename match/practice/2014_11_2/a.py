
n = int(raw_input())
k = int(raw_input())

M = []
for i in xrange(n+3):
  M.append([0]*(n+1)+[0,0])

for i in xrange(k):
  v, x, y = map(int, raw_input().split())
  M[x][y] = v

ans = 0
def move(d, v, xx, yy):
  global ans
  if d == 'L':
    for i in xrange(1, n+1):
      ind = 0
      p = 1
      flag = 1
      while p <= n:
        if flag:
          while p <= n and M[i][p] == 0:
            p += 1
          pre = M[i][p]
          p += 1
          flag = 0

        while p <= n and M[i][p] == 0:
          p += 1
          
        if pre == M[i][p] and pre:
          ind += 1
          M[i][ind] = pre<<1
          ans += pre<<1
          
          flag = 1
        elif pre:
          ind += 1
          M[i][ind] = pre
          pre = M[i][p]

        p += 1

      if not flag and pre:
        ind += 1
        M[i][ind] = pre

      for x in xrange(ind+1, n+1):
        M[i][x] = 0
  elif d == 'R':
    for i in xrange(1, n+1):
      ind = n+1
      p = n
      flag = 1
      while p:
        if flag:
          while p and M[i][p] == 0:
            p -= 1
          pre = M[i][p]
          if p:p -= 1
          flag = 0

        while p and M[i][p] == 0:
          p -= 1
        if pre == M[i][p] and pre:
          ind -= 1
          M[i][ind] = pre<<1
          ans += pre<<1
          flag = 1
        elif pre:
          ind -= 1
          M[i][ind] = pre
          pre = M[i][p]

        if p:p -= 1

      if not flag and pre:
        ind -= 1
        M[i][ind] = pre

      for x in xrange(1, ind):
        M[i][x] = 0
  elif d == 'U':
    for i in xrange(1, n+1):
      ind = 0
      p = 1
      flag = 1
      while p <= n:
        if flag:
          while p <= n and M[p][i] == 0:
            p += 1
          pre = M[p][i]
          p += 1
          flag = 0

        while p <= n and M[p][i] == 0:
          p += 1
        if pre == M[p][i] and pre:
          ind += 1
          M[ind][i] = pre<<1
          ans += pre<<1
          flag = 1
        elif pre:
          ind += 1
          M[ind][i] = pre
          pre = M[p][i]

        p += 1

      if not flag and pre:
        ind += 1
        M[ind][i] = pre

      for x in xrange(ind+1, n+1):
        M[x][i] = 0
  elif d == 'D':
    for i in xrange(1, n+1):
      ind = n+1
      p = n
      flag = 1
      while p:
        if flag:
          while p and M[p][i] == 0:
            p -= 1
          pre = M[p][i]
          if p:p -= 1
          flag = 0

        while p and M[p][i] == 0:
          p -= 1
        if pre == M[p][i] and pre:
          ind -= 1
          M[ind][i] = pre<<1
          ans += pre<<1
          flag = 1
        elif pre:
          ind -= 1
          M[ind][i] = pre
          pre = M[p][i]

        if p:p -= 1

      if not flag and pre:
        ind -= 1
        M[ind][i] = pre

      for x in xrange(1, ind):
        M[x][i] = 0
  M[xx][yy] = v


def out():
  print
  for i in xrange(1, n+1):
    for j in xrange(1, n+1):
      print M[i][j],
    print
  print

l = int(raw_input())
#out()
for i in xrange(l):
  d, v, x, y = raw_input().split()
  v, x , y = map(int, [v, x, y])
  move(d, v, x, y)
  #out()

print ans
