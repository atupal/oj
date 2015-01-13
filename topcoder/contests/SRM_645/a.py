class BacteriesColony:

  def performTheExperiment(self, c):
    l = len(c)
    if l < 3:
      return c
    while 1:
      flag = 1
      a = [0] * l
      a[0] = c[0]
      a[l-1] = c[l-1]
      for i in xrange(1, l-1):
        if c[i-1] > c[i] and c[i+1] > c[i]:
          a[i] = c[i]+1
          flag = 1
        elif c[i-1] < c[i] and c[i+1] < c[i]:
          a[i] = c[i]-1
          flag = 1
        else:
          a[i] = c[i]
      if not flag:
        return a
      c = a
