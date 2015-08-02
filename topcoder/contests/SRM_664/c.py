#!/bin/sh
# -*- coding: utf-8 -*-
''''which python2 >/dev/null && exec python2 "$0" "$@" # '''
''''which python  >/dev/null && exec python  "$0" "$@" # '''

T = [0]*50
cnt = 0

def mergeSort(left,right):
    if left+1 >= right: return

    mid = (left + right) / 2
    mergeSort(left,mid)
    mergeSort(mid,right)

    # then merge the two halves together
    merged = []    # an empty sequence
    p1 = left
    p2 = mid
    while (p1 < mid) or (p2 < right):
        if p1 == mid:
            merged.append( T[p2] )
            p2 += 1
        elif p2 == right:
            merged.append( T[p1] )
            p1 += 1
        else:
            global cnt
            cnt += 1
            if T[p1] < T[p2]:
                merged.append( T[p1] )
                p1 += 1
            else:
                merged.append( T[p2] )
                p2 += 1

    # finally, move the merged elements back into the original array
    for i in xrange(left, right):
        T[i] = merged[i-left]

class BearSortsDiv2:

    def getProbability(self, seq):
        for i in xrange(len(seq)):
            T[seq[i]-1] = i;

        mergeSort(0, len(seq))

        return -0.6931471805599453 * cnt


b = BearSortsDiv2()

print b.getProbability([0,13,18,2,4,6,24,22,19,5,7,20,23,14,21,17,25,3,1,11,12,8,15,16,9])
