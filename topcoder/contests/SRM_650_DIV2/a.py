# -*- coding: utf-8 -*-


class TaroJiroDividing:

  def getNumber(self, A, B):
    a = set()
    b = set()
    while A&1==0:
      a.add(A)
      A /= 2
    while B&1==0:
      b.add(B)
      B /= 2
    a.add(A)
    b.add(B)

    cnt = 0
    for i in a:
      if i in b:
        cnt += 1

    return cnt


