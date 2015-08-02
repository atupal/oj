#!/bin/sh
# -*- coding: utf-8 -*-
''''which python2 >/dev/null && exec python2 "$0" "$@" # '''
''''which python  >/dev/null && exec python  "$0" "$@" # '''


class BearCheats:

    def eyesight(self, A, B):

        A = str(A)
        B = str(B)
        cnt = 0
        for i in xrange(len(A)):
            if A[i] != B[i]:
                cnt += 1

        if cnt > 1:
            return "glasses"

        return "happy"
