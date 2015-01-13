
class JanuszInTheCasino:

  def __init__(self):
    self.memo = {}

  def dp(self, n, m, k):
    key = (n, m, k)
    if key in self.memo: return self.memo[key]

    r = n%m
    q = n/m

    if k==1:
      if n>=2:
        ret=1.
      elif n>=1:
        ret = (m-1)*1./m
      else:
        ret = 0.
    else:
      ret =  self.dp(n-q, m, k-1)*(m-r)*1./m
      ret += self.dp(n-q-1, m, k-1)*r*1./m
    self.memo[key] = ret
    return ret

  def findProbability(self, n, m, k):
    if m<2:return 0
    return self.dp(n, m, k)

j = JanuszInTheCasino()

print j.findProbability(3, 2, 2)
print j.findProbability(1, 3, 3)
print j.findProbability(4, 3, 2)
print j.findProbability(5, 4, 5)
print j.findProbability(1000000000000, 2, 40)
