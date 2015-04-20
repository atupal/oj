#!/bin/sh
# -*- coding: utf-8 -*-
''''which python2 >/dev/null && exec python2 "$0" "$@" # '''
''''which python  >/dev/null && exec python  "$0" "$@" # '''

F = [55, 89]
a = [15, 66]
b = [20, 44]

for i in xrange(100):
    x = a[0]*F[0] + a[1]*F[1]
    y = b[0]*F[0] + b[1]*F[1]
    if x > y:
        a[0] -= b[0]
        a[1] -= b[1]
        print a, b
        print a[0], a[1], a[0]*F[0]+a[1]*F[1]
    elif y > x:
        b[0] -= a[0]
        b[1] -= a[1]
        print a, b
        print b[0], b[1], b[0]*F[0]+b[1]*F[1]
    else:
        print 'haha'
        print a[0], a[1], b[0], b[1], x
        break
