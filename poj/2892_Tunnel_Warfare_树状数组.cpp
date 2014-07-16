/*
   被摧毁 为 1，为摧毁为 0
   连续区间即为 sumseek(sum(x)) 到 sumseek(sum(x)+1) 之间
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lowbit(x) ((x)&(-x))

const int maxn = 50010;
int n, m;
int bit[maxn] = {0};

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

int sum(int x) {
  int ret = 0;
  while (x) {
    ret += bit[x];
    x -= lowbit(x);
  }
  return ret;
}

//寻找部分和为k的第一个位置 
int sumseek(int k) {
  int ans = 0, sum = 0;
  for (int i = 16; i >= 0; -- i) {
    ans += (1 << i);
    if (ans >= n or sum + bit[ans] >= k) ans -= (1 << i);
    else sum += bit[ans];
  }
  return ans + 1;
}


int lastd[maxn];
int dcnt = 0;

void solve() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; ++ i) {
    char op[2];
    int x, l, r;
    scanf("%s", op);
    if (op[0] == 'D') {
      scanf("%d", &x);
      lastd[++dcnt] = x;
      modify(x, 1);
    } else if (op[0] == 'Q') {
      scanf("%d", &x);
      l = sumseek(sum(x));
      if (l == 1 and get(1) == 0) -- l;
      if (l == x) printf("0\n");
      else {
        r = sumseek(sum(x)+1);
        if (r == n and get(n) == 0) ++ r;
        printf("%d\n", r - l - 1);
      }
    } else if (op[0] == 'R') {
      modify(lastd[dcnt--], -1);
    }
  }
}

int main() {
  solve();
  return 0;
}
