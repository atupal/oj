/*
ID: atupal1
PROB: frac1
LANG: C++11
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

const int maxn = 161;
int vis[maxn][maxn];
int cnt;
struct S {
  int p, q;
} s[maxn*maxn];
int n;

int gcd(int a, int b) {
  if (a && b) {
    while (a%=b^=a^=b^=a);
  }
  return a + b;
}

int cmp(S a, S b) {
  return a.p*b.q < b.p*a.q;
}

void solve() {
  cnt = 0;
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j < i; ++ j) {
      int x = j/gcd(i, j);
      int y = i/gcd(i, j);
      if (!vis[x][y]) {
        vis[x][y] = 1;
        s[cnt].p = x;
        s[cnt].q = y;
        cnt ++;
      }
    }
  }

  sort(s, s+cnt, cmp);
  printf("0/1\n");
  for (int i = 0; i < cnt; ++ i) {
    printf("%d/%d\n", s[i].p, s[i].q);
  }
  printf("1/1\n");

}

int main() {
  char *HOME = getenv("HOME");
  if (strcmp(HOME, "/home/atupal") != 0) {
    freopen("frac1.in", "r", stdin);
    freopen("frac1.out","w", stdout);
  }
  scanf("%d", &n);
  solve();

  return 0;
}

