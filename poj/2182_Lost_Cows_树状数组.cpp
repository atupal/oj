/*
   从第 n 个 cow 开始，插空位。找到 x+1 个空位就可以了
   用树状数组求空位
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lowbit(x) ((x)&(-x))

const int maxn = 8010;
int n;
int cache[maxn];
int bit[maxn];
int ans[maxn];

void modify(int x, int delta) {
  while (x <= n) {
    bit[x] += delta;
    x += lowbit(x);
  }
}

int get(int x) {
  int ans = bit[x];
  int z = x - lowbit(x);
  -- x;
  while (x != z) {
    ans -= bit[x];
    x -= lowbit(x);
  }
  return ans;
}

int sumseek(int k) {
  int ans = 0, sum = 0;
  for (int i = 13; i >= 0; -- i) {
    ans += (1<<i);
    if (ans >= n or sum + bit[ans] >= k) ans -= (1<<i);
    else {
      sum += bit[ans];
    }
  }
  return ans + 1;
}

void solve() {
  scanf("%d", &n);
  bit[1] = lowbit(1);
  cache[1] = 1;
  for (int i = 2; i <= n; ++ i) {
    bit[i] = lowbit(i);
    scanf("%d", cache+i);
    ++ cache[i];
  }
  int t;
  for (int i = n; i; -- i) {
    t = sumseek(cache[i]);
    modify(t, -1);
    ans[i] = t;
  }
  for (int i = 1; i <= n; ++ i) {
    printf("%d\n", ans[i]);
  }
}

int main() {
  solve();
  return 0;
}
