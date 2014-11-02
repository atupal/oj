#!/usr/bin/env python2

import requests
def get(problem_id):
  url = 'https://projecteuler.net/problem=%d' % problem_id
  r = requests.get(url)
 
if __name__ == '__main__':
  print get(16)
