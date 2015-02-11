class CartInSupermarketEasy:

  def calc(self, N, K):
    a = [N]
    k = 0
    while K:
      a.sort(reverse=True)
      if a[0] == 1: break
      k += 1

      b = []
      c = []
      cnt = 0
      for m in a:

        if a.count(m) > K:
          K = 0
          k -= 1
          break

        if m == 1: break

        b.append(m)

        c.append( m/2 )
        c.append( m-m/2 )

        cnt += 1

      K -= cnt

      for i in b:
        a.remove(i)
      for i in c:
        a.append(i)


    return k + max(a)

c = CartInSupermarketEasy()

print c.calc( 5,0 )
print c.calc( 5,2 )
print c.calc( 15,4 )
print c.calc( 45,5 )
print c.calc( 100, 100)
