class TheGridDivTwo:

  def __init__(self):
    self.vis = set()
    self.ans = 0

  def dfs(self, x, y, remain):
    if remain<0: return
    if (x, y) in self.vis: return
    if x+remain <= self.ans: return
    self.ans = max(self.ans, x)
    self.vis.add((x,y))
    for dx, dy in [ (1, 0), (0, 1), (0, -1), (-1, 0)]:
      self.dfs(x+dx, y+dy, remain-1)

  def find(self, x, y, k):
    import sys
    sys.setrecursionlimit(1500)
    for i in zip(x, y):
      self.vis.add(i)
    self.dfs(0, 0, k)
    return self.ans

import time
t = TheGridDivTwo()
st = time.time()


x = [1]
y = [0]

print time.time() - st
