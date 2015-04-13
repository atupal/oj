# -*- coding: utf-8 -*-


class Similars(object):

    def maxsim(self, L, R):
        s = []
        for i in xrange(L, R+1):
            s.append( sorted( list(set([_ for _ in str(i)]) ) ) )

        s.sort()

        ans = 0
        for i in xrange(len(s)-1):
            t = len( set(s[i]) & set(s[i+1]))
            if t > ans:
                ans = t

        return ans


if __name__ == '__main__':

    s = Similars()

    #print s.maxsim(1, 10)
    #print s.maxsim(1, 99)
    #print s.maxsim(444, 454)
    print s.maxsim(1, 100000)
    print s.maxsim(998, 1013)
