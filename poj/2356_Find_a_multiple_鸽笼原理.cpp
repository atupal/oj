/*
   a1,a2,a3...am是正整数序列，至少存在整数k和r,1<=k<r<=m,使得ak+a(k+1)+...+a(r)是m的倍数。

   证明比较简单:

   Sk表示前k个数之和，

    (1)若Sk%m==0,前k个数就是m的倍数

    （2）如果Sn与St模m同余，那么从t+1到n这些数之和模m等于0.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 15000;
int n;
int s[maxn];
int pos[maxn];

void solve () {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d", s+i);
  }
  memset(pos, -1, sizeof(pos));
  int sum = 0;;
  for (int i = 0; i < n; ++ i) {
    sum += s[i] % n;
    sum %= n;
    if (sum == 0) {
      printf("%d\n", i+1);
      for (int x = 0; x <= i; ++ x) {
        printf("%d\n", s[x]);
      }
      return;
    } else {
      if (pos[sum] == -1) pos[sum] = i;
      else {
        printf("%d\n", i-pos[sum]);
        for (int x = pos[sum]+1; x <= i; ++ x) {
          printf("%d\n", s[x]);
        }
        return;
      }
    }
  }
}

int main() {
  solve();

  return 0;
}
