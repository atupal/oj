/*
ID:atupal1
PROB:skidesign
LANG:C++11
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;
int a[1001];

void solve() {
  int min = 1e9;
  for (int i = 0; i < 101; ++ i) {
    int cnt = 0;
    for (int j = 0; j < n; ++ j) {
      if ( a[j] < i) {
        cnt += (i-a[j]) * (i-a[j]);
      } else if (a[j] > i + 17) {
        cnt += (a[j] - i - 17) * (a[j] - i - 17);
      }
    }
    if (cnt < min) min = cnt;
  }

  printf("%d\n", min);
}

int main() {
  freopen("skidesign.in", "r", stdin);
  freopen("skidesign.out","w", stdout);
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d", a+i);
  }
  solve();

  return 0;
}

