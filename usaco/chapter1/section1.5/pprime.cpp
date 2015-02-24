/*
ID: atupal1
PROG: pprime
LANG: C++11
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;

int a,b;
const int maxn = 1e8+1;
int isprime(int x);
int ans[10001];
int idx;

inline
void gen(int x) {
  int s[20];
  int cnt = 0;
  int n = x;
  while (n) {
    s[cnt++] = n%10;
    n /= 10;
  }
  int g = x;
  for (int i = 0; i < cnt; ++ i) {
    g = g*10 + s[i];
  }
  if (isprime(g)) {
    ans[idx++] = g;
  }

  g = x;
  for (int i = 1; i < cnt; ++ i) {
    g = g*10 + s[i];
  }
  if (isprime(g)) {
    ans[idx++] = g;
  }
}

inline
int isprime(int x) {
  if (!(x >= a && x <= b)) {
    return 0;
  }
  for (int i = 2; i*i <= x; ++ i) {
    if (x % i == 0) return 0;
  }
  return 1;
}

void solve() {
  idx = 0;
  for (int i = 1; i <= 10000; ++ i) {
    gen(i);
  }
  sort(ans, ans+idx);
  for (int i = 0; i < idx; ++ i) {
    printf("%d\n", ans[i]);
  }
}

int main() {
  char *HOME = getenv("HOME");
  if (strcmp(HOME, "/home/atupal") != 0) {
    freopen("pprime.in", "r", stdin);
    freopen("pprime.out","w", stdout);
  }
  scanf("%d %d", &a, &b);
  solve();

  return 0;
}

