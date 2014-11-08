# -*- coding: utf-8 -*-
"""
n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
"""

#mmap = lambda f, l: [] if not l else [f(l[0])] + mmap(f, l[1:])
#map = (lambda self, x: self(self, x)) (mmap, [])

print reduce( lambda a,b:a+b, 
    map(int, 
      (lambda x: (lambda s: '%d' % s)(x))  (
      (lambda x: ( lambda self, n: self(self, n) ) 
      (lambda f, n: 1 if n <= 1 else n*f(f, n-1), x) )(100) ) ) )
