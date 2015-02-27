/*
ID: atupal1
PROB: hamming
LANG: C++11
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 1000;
int n, b, d;

int gethamming(int a, int b) {
  a = a^b;
  int cnt = 0;
  while (a) {
    if (a&1) cnt ++;
    a >>= 1;
  }
  return cnt;
}

void solve() {
  int ans[maxn];
  ans[0] = 0;
  int cnt=1;
  for (int i = 1; i < (1<<b); ++ i) {
    int flag = 1;
    for (int j = 0; j < cnt; ++ j) {
      if (gethamming(ans[j], i) < d) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      ans[cnt++] = i;
    }
  }
  for (int i = 1; i <= n-n%10; ++ i) {
    if (i%10) {
      printf("%d ", ans[i-1]);
    } else {
      printf("%d\n", ans[i-1]);
    }
  }

  for (int i = 0; i < n%10-1; ++ i) {
    printf("%d ", ans[n-n%10+i]);
  }
  if (n%10)
    printf("%d\n", ans[n-1]);
}

int main() {
  char *HOME = getenv("HOME");
  if (strcmp(HOME, "/home/atupal") != 0) {
    freopen("hamming.in", "r", stdin);
    freopen("hamming.out","w", stdout);
  }
  scanf("%d %d %d", &n, &b, &d);
  solve();

  return 0;
}

