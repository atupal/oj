# -*- coding: utf-8 -*-
"""
If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?


NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
"""

s = """
one
two
three
four
five
six
seven
eight
nine
ten
eleven
twelve
thirteen
fourteen
fifteen
sixteen
seventeen
eighteen
nineteen
""".strip().split()

ss = """
twenty
thirty
forty
fifty
sixty
seventy
eighty
ninety
""".strip().split()

sss = """
hundred
thousand
""".strip().split()

def count(i):
  ans = 0
  if i >= 100:
    ans += len(s[i/100-1]) + len(sss[0])
    i = i % 100
    if i > 19:
      ans += len('and')
      ans += len( ss[i/10-2] )
      if i%10:
        ans += len( s[i%10-1] )
    elif i>0:
      ans += len('and')
      ans += len(s[i-1])
  else:
    if i > 19:
      ans += len( ss[i/10-2] )
      if i%10:
        ans += len( s[i%10-1] )
    else:
      ans += len(s[i-1])
  return ans

ans = len(sss[1]) + len(s[0])

for i in xrange(1, 1000):
  ans += count(i)

print ans
