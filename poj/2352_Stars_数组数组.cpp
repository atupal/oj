/*
   在线算法：统计 x 上的星星就可以了，求前缀和就是 level 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lowbit(a) (a&(-a))

const int maxn = 32010;
int n;
int ans[maxn] = {0};
int bit[maxn] = {0};
int max = 0;
int cx[maxn];
int cy[maxn];

void modify(int p, int delta) {
  while (p <= max) {
    bit[p] += delta;
    p += lowbit(p);
  }
}

int sum(int x) {
  int ans = 0;
  while (x) {
    ans += bit[x];
    x -= lowbit(x);
  }
  return ans;
}

void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d %d", cx+i, cy+i);
    // 这里注意 +1， 因为坐标可能为0，为 0调用 modify 会陷入死循环导致tle了几次。。。
    // 另：c++ 比 g++ 快了3 到 4 倍。。。
    ++ cx[i];
    ++ cy[i];
    max = cx[i] > max ? cx[i] : max;
  }

  for (int i = 0; i < n; ++ i) {
    ++ ans[sum(cx[i])];
    modify(cx[i], 1);
  }

  for (int i = 0; i < n; ++ i) {
    printf("%d\n", ans[i]);
  }
}

int main() {
  solve();
  return 0;
}
