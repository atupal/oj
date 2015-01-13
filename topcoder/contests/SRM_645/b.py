

class ConnectingCars():
  
  def get(self, x):
    ret = 0
    for i in xrange(len(self.car)):
      ret += abs( self.car[i][0] - x )
      x += self.car[i][1]
    return ret

  def minimizeCost(self, positions, lengths):
    self.car = zip(positions, lengths)
    self.car.sort()
    low = self.car[0][0]
    high = self.car[-1][0]+self.car[-1][1]-sum(lengths)
    while low < high-2:
      #print low, high
      mid = low + (high-low)/3.;
      midmid = high - (high-low)/3.;
      x1 = self.get(mid)
      x2 = self.get(midmid)
      if x1 < x2:
        high = midmid 
      else:
        low = mid

    return int( min(self.get(low), self.get(high), self.get(low+1)) )


c = ConnectingCars()
print c.minimizeCost([1, 3, 10, 20], [2, 2, 5, 3])
