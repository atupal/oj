#!/bin/sh
# -*- coding: utf-8 -*-
''''which python2 >/dev/null && exec python2 "$0" "$@" # '''
''''which python  >/dev/null && exec python  "$0" "$@" # '''


from random import randint
n = randint(4, 4)
print n

x = randint(0, 5)

g = 1
for i in xrange(x):
  g *= randint(2, 10)

for i in xrange(n):
  print randint(1, 20)
