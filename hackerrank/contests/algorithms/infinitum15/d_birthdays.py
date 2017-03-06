#!/bin/sh
# -*- coding: utf-8 -*-
''''which python2 >/dev/null && exec python2 "$0" "$@" # '''
''''which python  >/dev/null && exec python  "$0" "$@" # '''


p1 = [1] * 368
p2 = [1] * 368

for n in xrange(1, 368):

    leapcnt = n / 4

    tmp = 365

    for i in xrange(n-leapcnt):
        p1[n] *= tmp
        p2[n] *= 365
        tmp -= 1

    tmp += 1
    for i in xrange(leapcnt):
        p1[n] *= tmp
        p2[n] *= 366
        tmp -= 1


n = int(raw_input())

for i in xrange(n):

    p = float(raw_input())

    p = int(p * 1000)

    for ans in xrange(1, 368):

        if (p2[ans]-p1[ans])*1000 >= p2[ans] * p:

            print ans
            break
