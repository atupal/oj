
class DecipherabilityEasy:
  
  def check(self, s, t):

    for i in xrange(len(s)):

      if s[:i] + s[i+1:] == t:
        return "Possible"

    return 'Impossible'
