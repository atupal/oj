#!/usr/bin/env python2

import requests

s = requests.Session()

user = 'atupal'
password = ''

data = {
    'user_id1': user,
    'password1': password,
    'B1': 'login',
    'url': '/',
    }

r = s.post('http://poj.org/login', data=data, allow_redirects=0)


proxy_password = ''
http_proxy = {
    'http': 'http://atupal:%s@j10.jayproxy.org:3000' % proxy_password
    }

import sys

with open(sys.argv[1]) as fi:
  data = {
      'problem_id': sys.argv[1].split('_')[0],
      'language': '4',
      'source': fi.read(),
      'submit': 'Submit'
  }

s.post('http://poj.org/submit', proxies=http_proxy, data=data)

from bs4 import BeautifulSoup
import os
import time

def colorful_print(text, color='red'):
  color_dict = {
      'red': '\033[31m',
      }
  print color_dict[color]+text+'\033[0m',

while 1:
  try:
    r = s.get('http://poj.org/status')
    soup = BeautifulSoup(r.text)
    os.system('cls')
    for tr in soup('tr')[1:13]:
      flag = 0
      for td in tr('td'):
        if user in td.text:
          flag = 1
          break
      for td in tr('td'):
        if flag:
          colorful_print(td.text)
        else:
          print td.text,
      print
    print '-' * 100
    time.sleep(1)
  except KeyboardInterrupt:
    exit(0)

