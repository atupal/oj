# -*- coding: utf-8 -*-

class mydict(dict):

  def __missing__(self, key):
    self[key] = 999999999
    return self[key]


class TaroFillingAStringDiv2:

  def getNumber(self, s):

    dp = [ mydict() for i in s ]
    if s[0] != '?':
      dp[0][s[0]] = 0
    else:
      dp[0]['A'] = 0
      dp[0]['B'] = 0

    for i in xrange(1, len(s)):
      if s[i] == '?':
        dp[i]['A'] = min( dp[i-1]['A']+1, dp[i-1]['B'] )
        dp[i]['B'] = min( dp[i-1]['B']+1, dp[i-1]['A'] )
      elif s[i] == 'A':
        dp[i]['A'] = min( dp[i-1]['A']+1, dp[i-1]['B'])
      else:
        dp[i]['B'] = min( dp[i-1]['B']+1, dp[i-1]['A'])


    return min( dp[len(s)-1]['A'], dp[len(s)-1]['B'] )

t = TaroFillingAStringDiv2()

if __name__ == '__main__':
  print t.getNumber('ABAA')
  print t.getNumber('??')
  print t.getNumber('A?A')
  print t.getNumber('AAAB'*50)
  print t.getNumber('?'*50)
