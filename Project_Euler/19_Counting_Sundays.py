# -*- coding: utf-8 -*-
"""
You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
"""
m = [30] * 12
for i in [1, 3, 5, 7, 8, 10, 0]:
  m[i] = 31

cnt = 365 - m[0]
ans = 0
for year in xrange(1901, 2001):
  m[2] = 28
  if ( year % 100 != 0 and year % 4 == 0 ) or (year % 400 == 0):
    m[2] = 29
  for month in xrange(1,13):
    cnt += m[month-1]
    if cnt % 7 == 6:
      ans += 1

print ans
