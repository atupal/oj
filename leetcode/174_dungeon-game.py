
class Solution:
  # @param dungeon, a list of lists of integers
  # @return a integer
  def calculateMinimumHP(self, map):
    dp = []
    pre = []
    for i in xrange(len(map)):
        dp.append([0]*len(map[0]))
        pre.append([0]*len(map[0]))

    def get(init):
      dp[0][0] = init+map[0][0]
      if dp[0][0] < 1:
        return 0
      for i in xrange(1, len(map[0])):
        if dp[0][i-1] > 0:
          dp[0][i] = dp[0][i-1] + map[0][i]
          pre[0][i] = 1
        else:
          dp[0][i] = -1

      for i in xrange(1, len(map)):
        if dp[i-1][0] > 0:
          dp[i][0] = dp[i-1][0] + map[i][0]
          pre[i][0] = 2
        else:
          dp[i][0] = -1

      for i in xrange(1, len(map)):
        for j in xrange(1, len(map[0])):
          if dp[i][j-1] <= 0 and dp[i-1][j] <= 0:
            dp[i][j] = -1
            continue
          if dp[i][j-1] > dp[i-1][j]:
            dp[i][j] = dp[i][j-1] + map[i][j]
            pre[i][j] = 1
          else:
            dp[i][j] = dp[i-1][j] + map[i][j]
            pre[i][j] = 2

      return dp[-1][-1] > 0

    low = 1;high = 1000000000
    while low < high:
      mid = (low+high)>>1
      if not get(mid):
        low = mid+1
      else:
        high = mid
    return low

s = Solution()
print s.calculateMinimumHP([[-61,-52,10,-82],[-77,-22,-83,48],[-59,-61,-42,-34],[231,47,-6,19]])
