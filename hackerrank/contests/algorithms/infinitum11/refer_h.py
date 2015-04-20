from fractions import gcd

'''
Note: we represent the matrix
[a+b a]
[a   b]
with the pair (a,b)
'''

def mmul((a,b),(c,d),m):
    '''
    Multiply the matrices (a,b) and (c,d), i.e.

    [a+b a]         [c+d c]
    [a   b]   and   [c   d]
    '''
    bd = b*d
    return (
        ((a+b)*(c+d) - bd) % m,
        (a*c + bd) % m,
    )

def mpow(b,e,m):
    ''' raise the matrix b to the power e, modulo m '''
    if e == 0:
        return 0, 1
    if e == 1:
        return b
    if e & 1:
        return mmul(mpow(b,e-1,m), b, m)
    return mpow(mmul(b,b,m), e>>1, m)

def Fm(n,m):
    ''' Find F(n) and F(n+1) modulo m '''
    b,d = mpow((1,0), n, m)
    return b, (b+d) % m

def Gm(a0,a1,n,m):
    ''' Find a0*F(n) + a1*F(n+1) modulo m '''
    f0, f1 = Fm(n,m)
    return (a0*f0 + a1*f1) % m

def answer(n, m, a0=0, a1=0, a2=0, b0=0, b1=0, b2=0):
    if a2 or b2:
        return answer(n, m, a0=a0+a2, a1=a1+a2, b0=b0+b2, b1=b1+b2)

    if b1:
        q, r = divmod(a1, b1)
        return answer(n, m, a0=b0, a1=b1, b0=a0 - q*b0, b1=r)

    # adjust sign
    if b0 < 0:
        b0 = -b0

    if a1 == 0:
        # easy case
        f0, f1 = Fm(n,m)
        return gcd(a0,b0) * f0 % m

    if b0 == 0:
        # another easy case
        return Gm(a0,a1,n,m)

    # general case
    f0, f1 = Fm(n, a1*b0)
    g = gcd(a1, f0)
    return gcd(a0*f0 + a1*f1, g*b0) % m

z = input()
for cas in xrange(z):
    n, a0, a1, a2, b0, b1, b2, m = map(int, raw_input().strip().split())
    print answer(n, m, a0, a1, a2, b0, b1, b2)
