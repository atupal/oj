#!/usr/bin/env python2
# -*- coding: utf-8 -*-

"""
    submit.py
    ~~~~~~~~~

    submit code to poj
    usage:
      ./submit.py file_name
    file_name format: probmenId_xxx.c/cpp
"""

import requests
import sys
import os
import time

from bs4 import BeautifulSoup

s = requests.Session()
try:
  with open('./user') as fi:
    user = fi.readline().strip()
    password= fi.readline().strip()
except:
  print 'read user file failed, use default username, password'
  user = 'atupal'
  password = ''

proxy_password = ''
http_proxy = {
    'http': 'http://atupal:%s@j10.jayproxy.org:3000' % proxy_password
    }

def login():
  data = {
      'username': user,
      'userpass': password,
      'login': 'Sign In'
      }
  headers = {
      'Host': 'acm.hdu.edu.cn',
      'Origin': 'http://acm.hdu.edu.cn',
      'Referer': 'http://acm.hdu.edu.cn/status.php',
      'User-Agent:': 'chrome',
      }
  
  r = s.post('http://acm.hdu.edu.cn/userloginex.php?action=login', data=data, allow_redirects=0, headers=headers)
  print r



def submit_code():
  with open(sys.argv[1]) as fi:
    data = {
        'check': '0',
        'problemid': sys.argv[1].split('_')[0],
        'language': '2',
        'usercode': fi.read()
    }
    headers = {
        'Host': 'acm.hdu.edu.cn',
        'Origin': 'http://acm.hdu.edu.cn',
        'Referer': 'http://acm.hdu.edu.cn/submit.php?pid=%s' % data['problemid'],
        'User-Agent:': 'chrome',
        }
  
  r = s.post('http://acm.hdu.edu.cn/submit.php?action=submit', proxies=http_proxy, data=data, headers=headers)
  print r


def colorful_print(text, color='red'):
  color_dict = {
      'red': '\033[31m',
      }
  print color_dict[color]+text+'\033[0m',


def fetch_result():
  while 1:
    try:
      r = s.get('http://acm.hdu.edu.cn/status.php')
      soup = BeautifulSoup(r.text)
      os.system('cls')
      time.sleep(0.2)
      for tr in soup('tr')[9:17]:
        flag = 0
        for td in tr('td'):
          if user in td.text or 'kangle' in td.text:
            flag = 1
            break
          elif 'BoardHome' in td.text:
            flag = 2
            break
        if flag == 2:
          continue
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

def main():
  if len(sys.argv) > 1 and sys.argv[1].lower() != 'status':
    login()
    submit_code()
  fetch_result()

if __name__ == '__main__':
  main()
