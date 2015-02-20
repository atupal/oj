#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 1100000;
int n, m, k;
int x;
int a[maxn];

int main() {
  scanf("%d %d %d", &n, &m, &k);
  scanf("%d", &x);
  for (int i = 0; i < m; ++ i) {
    scanf("%d", &a[i]);
    a[i] ^= x;
  }
  int ans = 0;
  for (int i = 0; i < m; ++ i) {
    int cnt = 0;
    while (a[i]) {
      if (a[i]&1) {
        cnt += 1;
      }
      a[i] >>= 1;
    }
    if (cnt <= k) ans += 1;
  }
  printf("%d\n", ans);

  return 0;
}
