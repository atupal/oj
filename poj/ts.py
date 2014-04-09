
class FoxAndSightseeing:

  def getMin(self, s):
    m = -1
    for i in xrange(1, len(s)-1, 1):
      t = 0
      for x in xrange(i-1):
        t += abs(s[x+1]-s[x])
      for x in xrange(i+1,len(s)-1,1):
        t += abs(s[x+1]-s[x])
      t += abs(s[i-1] - s[i+1])
      if t < m or m == -1:
        m = t
    return m

ans = -1
class ColorfulRoad:

  def getMin(self, r):
    global ans
    ans=-1
    l = len(r)

    def dfs(ind , cost):
      global ans
      if ind==l-1:
        if cost < ans or ans ==-1:
          ans = cost

      if r[ind]=='R':
        for i in xrange(ind+1, len(r)):
          if r[i] == 'G':
            dfs(i, cost+(i-ind)**2)
      elif r[ind]=='G':
        for i in xrange(ind+1, len(r)):
          if r[i] == 'B':
            dfs(i, cost+(i-ind)**2)
      elif r[ind]=='B':
        for i in xrange(ind+1, len(r)):
          if r[i] == 'R':
            dfs(i, cost+(i-ind)**2)

    if r[0] != 'R':return -1
    dfs(0, 0)

    return ans


class SparseFactorialDiv2:
  def getCount(i):
    return ret

T = SparseFactorialDiv2()
for i in xrange(4, 30):
  xor
