#!/bin/sh
# -*- coding: utf-8 -*-
''''which python2 >/dev/null && exec python2 "$0" "$@" # '''
''''which python  >/dev/null && exec python  "$0" "$@" # '''

import numpy

from itertools import groupby

A = []
c = 6

for n in xrange(1<<c):
    A.append([0]*(1<<c))

for n in xrange(1<<c):

    cnt = 0
    for i in xrange(c):
        for j in xrange(i, c):
            mask = ( (1<<(j+1)) -1) - ( (1<<i)-1 )
            cnt += 1
            A[n][ n^mask ] += 1

    for m in xrange(1<<c):
        A[n][m] /= 1.0*cnt

bb = [-1]*(1<<c)
A = A[1:]
bb = bb[1:]
for i in xrange(len(A)):
    A[i] = A[i][1:]

for i in xrange(len(A)):
    A[i][i] = -1

tmp =[]
for a in A:
    cnt=0
    for i in a:
        if i==0:cnt+=1
    tmp.append(cnt)
print numpy.matrix(A)
ans = numpy.matrix(bb) * numpy.matrix(A).I
print ans
print tmp
ans = ans.tolist()
d={}
for i in ans[0]:
    i = int(i*1000000000)
    if i in d:
        d[i]+=1
    else:
        d[i]=1

print
print d
