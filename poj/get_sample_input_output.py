#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import requests
import sys
from lxml import html


def get_sample_input_output(problem_id):
  xpath = '//pre[@class="sio"]/text()'
  url = 'http://poj.org/problem?id=%s' % str(problem_id)
  ret = requests.get(url)
  ret = html.fromstring(ret.content).xpath(xpath)
  return ret[0], ret[1]

def test():
  pass

if __name__ == '__main__':
  if len(sys.argv) < 2:
    exit(0)
  print( 'input:\n' + '\n\noutput:\n'.join( get_sample_input_output(int(sys.argv[1]))) )
