#!/usr/bin/env python2

import urllib2
import lxml.html
import os, sys

def get(problem_id):
  url = 'https://projecteuler.net/problem=%d' % problem_id
  r = urllib2.urlopen(url).read()
  x = lxml.html.fromstring(r)
  title = x.xpath('//*[@id="content"]/h2/text()')[0]
  content = '\n'.join( x.xpath('//*[@id="content"]/div[3]/p/text()') )
  filename = '%d_%s.py' % (problem_id, '_'.join(title.split()) )
  if not os.path.exists(filename):
    with open(filename, 'w') as fi:
      fi.write('# -*- coding: utf-8 -*-\n')
      fi.write('"""\n')
      fi.write(content)
      fi.write('\n"""\n')

if __name__ == '__main__':
  if len(sys.argv) <= 1:
    exit(0)
  get(int(sys.argv[1]))
