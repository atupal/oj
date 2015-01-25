

class LostCharacter:

  def getmins(self, s):
    ans = []
    for i in xrange(len(s)):
      t = []
      for w in s[:i]:
        t.append(w.replace('?', 'z'))
      t.append(s[i].replace('?', 'a'))
      for w in s[i+1:]:
        t.append(w.replace('?', 'z'))
      t.sort()
      ans.append( t.index(s[i].replace('?', 'a')) )
    return tuple(ans)


if __name__ == '__main__':
  a = LostCharacter()
  print a.getmins([ 'a'*50 for i in xrange(50) ])
