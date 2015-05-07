#!/bin/sh
# -*- coding: utf-8 -*-
''''which python2 >/dev/null && exec python2 "$0" "$@" # '''
''''which python  >/dev/null && exec python  "$0" "$@" # '''

import numpy

from itertools import groupby

#c = 20

"""
描述
少女幽香这几天正在学习交换代数，然而她什么也没有学会，非常痛苦。于是她开始玩起了一个简单的小游戏，来放松一下。
地面上一共有n个球，一开始有一些是黑色的，有一些是白色的。每次她随机选择一个区间（一共有n(n+1)/2个区间，每个区间有相等的概率被选择），把这个区间的颜色反转，即将该区间中白球变黑球，黑球变白球。
现在她想要知道期望情况下，多少次反转能够使得整个区间都是白色的。

输入
第一行n (1 <= n <= 20)，表示球的数量。
接下来一行n个数，表示这些球的颜色，0表示白色，1表示黑色。

输出
一行一个实数，表示答案。你的答案与标准答案的绝对误差在10-4以内就算正确。

样例输入
2
0 1
样例输出
3.000000
"""


"""
将 （1..1<<c） 分成 klass 类，第 k 类需要 k 步 翻转才能为 0
        即 cs[i] = map(lambda x:x[0], groupby(bin(i)) ).count('1')
        然后在 guass 消元或者直接 b*(A'**-1)求解
        我们通过找规律可以发现每类的答案如果是一样的一定是的方程的解。。。


官方题解：
不妨假设颜色的序列是 a1,a2,...,an
我们再额外添加两个求 a0 和 an+1，且 a0=an+1=0
通常对于区间翻转，我们很容易想到做差,我们不妨令di=ai xor ai+1
我们考虑一次操作，翻转 ai,ai+1,...aj 容易发现只有两个 d，di-1 和 dj 的值发生了改变
同时可以发现 a1...an 都等于 0，等价于 d0..dn 都等于 0
那么通过这一步转化，问题就变成了，每次在 d0..dn中随机选择两个位置i-1和j，并且将他们翻转，
问变为全0的期望时间。
此时所有位置都是一样的了，我们只需要记录d序列中0的个数就可以了，
不妨令anscnt 表示 有 cnt 个 0 的话，变为全0的期望时间
注意到 cnt 经过一步操作，可能转移到 cnt-2,cnt,cnt+2中的一个，转移的概率是很容易计算的，
我们就可以列出关于 ans 的方程。
那么使用 O(n3) 的高斯消元，我们就能计算 anscnt，从而解决这个问题了。

"""

for c in xrange(1, 21):

    cs = [0]*(1<<c)
    
    for i in xrange(1<<c):
        cs[i] = map(lambda x:x[0], groupby(bin(i)) ).count('1')
        # print ('{:0%db}'%c).format(i), '->', cs[i]
    
    klass = max(cs)
    A = [None] * (klass+1)
    
    for n in xrange(1<<c):
        if A[ cs[n] ] is None:
            A[ cs[n] ] = [0] * (klass+1)
        else:
            continue
    
        for i in xrange(c):
            for j in xrange(i, c):
                mask = ( (1<<(j+1)) -1) - ( (1<<i)-1 )
                A[ cs[n] ][ cs[n^mask] ] += 1
    
    for i in xrange(len(A)):
        for j in xrange(len(A[0])):
            A[i][j] /= 1.0*c*(c+1)/2
    
    for i in xrange(len(A)):
        A[i][i] -= 1
    
    A = A[1:]
    
    for i in xrange(len(A)):
        A[i] = A[i][1:]
    
    A = numpy.matrix(A)
    b = [-1] * (klass)
    print '{',
    l = (b*A.T.I).tolist()[0]
    for xx in l[:-1]:
        print '%f,'%xx,
    print l[-1], '},'
