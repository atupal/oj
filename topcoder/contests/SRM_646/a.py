class TheConsecutiveIntegersDivTwo:

  def find(self, numbers, k):
    s = list(numbers)
    s.sort()
    if k==1:
      return 0

    ans = s[1]-s[0]
    for i in xrange( len(s)-1 ):
      ans = min(ans, s[i+1]-s[i])
    return ans
