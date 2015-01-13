"""
  O(nlogn)
"""
class Solution_sort:
  # @param num, a list of integer
  # @return an integer
  def maximumGap(self, num):
    if len(num) <= 1:return 0
    num.sort()
    return max([(num[i]-num[i-1]) for i in xrange(1, len(num))])

"""
  O(n)
"""
class Solution:
  # @param num, a list of integer
  # @return an integer
  def maximumGap(self, num):
    if len(num) <= 1:return 0
    gap = (max(num) - min(num))*1./(len(num)-1)
    bucket = [[] for _ in xrange(1+len(num))]
    first = min(num)
    for i in num:
      bucket[int((i-first)/gap)].append(i)

    ans = 0
    i = 1
    pre = max(bucket[0])
    while i < len(num):
      while not bucket[i]:
        i += 1
      ans = max(ans, min(bucket[i])-pre)
      pre = max(bucket[i])
      i += 1
    return ans

s = Solution()
print s.maximumGap([1,1,1,1,1,5,5,5,5,5])
