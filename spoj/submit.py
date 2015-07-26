#!/usr/bin/env python2
"""
    submit.py
    ~~~~~~~~~

    submit code to spoj
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

def login():
  data = {
      'login_user': user,
      'password': password,
      'autologin': '0',
      'next': '/',
      }

  login_url = 'http://www.spoj.com/login/'
  r = s.post(login_url, data=data, allow_redirects=1)
  print r


def submit_code():
  with open(sys.argv[1]) as fi:
    data = {
        'problemcode': sys.argv[1].split('_')[0],
        'file': fi.read(),
        'lang': '44',
        'submit': 'Send',
    }
  
  submit_url = 'http://www.spoj.com/submit/complete/'
  r = s.post(submit_url, data=data)
  print r
  if r.status_code != 200:
      print r.content


def colorful_print(text, color='red'):
  color_dict = {
      'red': '\033[31m',
      }
  print color_dict[color]+text+'\033[0m',


def fetch_result():
  status_url = 'http://www.spoj.com/status/ns=14750133'
  while 1:
    try:
      r = s.get(status_url)
      soup = BeautifulSoup(r.text)
      os.system('cls')
      time.sleep(0.2)
      for tr in soup('tr')[1:13]:
        flag = 0
        for td in tr('td'):
          if user in td.text:
            flag = 1
            break
          elif 'BoardHome' in td.text:
            flag = 2
            break
        if flag == 2:
          continue
        for td in tr('td'):
          if flag:
            colorful_print(td.text.strip())
          else:
            print td.text.strip(),
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
