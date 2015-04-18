#!/bin/sh
# -*- coding: utf-8 -*-
''''which python2 >/dev/null && exec python2 "$0" "$@" # '''
''''which python  >/dev/null && exec python  "$0" "$@" # '''

n = 10**5

print n

arr = [i+1 for i in xrange(n)]
from random import shuffle
shuffle(arr)

for i in arr:
    print i,

print
print n
for i in xrange(n):
    print i+1
