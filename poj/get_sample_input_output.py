# -*- coding: utf-8 -*-

import requests
import sys
from lxml import html


def get_sample_input_output(problem_id):
  xpath = '//pre[@class="sio"]/text()'
  url = 'http://poj.org/problem?id=%s' % str(problem_id)
  res = requests.get(url)
  ret = html.fromstring(res.content).xpath(xpath)
  return ret[0], ret[1]

def test():
  pass

if __name__ == '__main__':
  if sys.argc < 2:
    exit(0)
