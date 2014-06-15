#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

const int maxn = 10;
int n;
int d[maxn * maxn + maxn];

//int b[2][100002];
int b[100002];
int sum = 0;

int goal;

int input() {
  if (scanf("%d", &goal) == EOF) return 0;
  n = 0;
  int t;
  scanf("%d", &t);
  int w, cnt;
  for (int i = 0; i < t; ++ i) {
    scanf("%d %d", &cnt, &w);
    for (int x = 0; cnt > 0; ++ x) {
      int mask = 1 << x;
      if (cnt <= mask) {
        d[n++] = cnt * w;
      } else {
        d[n++] = mask * w;
      }
      sum += d[n-1];
      cnt -= mask;
    }
  }
  return 1;
}

void solve() {
  memset(b, 0, sizeof(b));
  for (int i = 1; i <= n; ++ i) {
    //now = i & 1;
    //pre = not now;
    /*由于只需要最后f[v]的值，倒推前一个物品，其实只要知道f[v-w[n]]即可。以此类推，对以第j个背包，其实只需要知道到f[v-sum{w[j..n]}]即可*/
    int below = max(d[i-1], goal - sum);
    sum -= d[i-1];
    for (int j = goal; j >= below; -- j) {
      b[j] = max(b[j], b[j-d[i-1]] + d[i-1]);
    }
  }
  printf("%d\n", b[goal]);
}

int main () {
  while (input()) {
    solve();
  }

  return 0;
}
