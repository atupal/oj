#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = (int) 1e5+10;
int n, k;
int a[maxn];

int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a%b);
}

void solve() {
  for (int i = 0; i < n; ++ i) {
    if (a[i] % k == 0) {
      a[i] /= k;
    } else {
      a[i] = 0;
    }
  }

  int g = 0;
  for (int i = 0; i < n; ++ i) {
    g = gcd(g, a[i]);
  }
  if (g == 1) {
    printf("YES\n");
    return;
  }
  printf("NO\n");
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++ i) {
    scanf("%d %d", &n, &k);
    for (int j = 0; j < n; ++ j) {
      scanf("%d", a+j);
    }
    solve();
  }

  return 0;
}

