# -*- coding: utf-8 -*-
"""
Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?
"""
import urllib2
url = 'https://projecteuler.net/project/resources/p022_names.txt'
text = urllib2.urlopen(url).read()
exec('s=[%s]' % text)
s.sort()
ans = 0
for i,v in enumerate(s):
  ans += (i+1)*(sum( map(ord, v.lower()) ) - len(v) * (ord('a') - 1))

print ans
