/*
ID: atupal1
PROG: sprime
LANG: C++11
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int n;
int cnt;
int ans[1000000];

int isprime(int x) {
  if (x <= 1) return 0;
  for (int i = 2; i*i <= x; ++ i) {
    if (x % i == 0) return 0;
  }
  return 1;
}

void dfs(int idx, int num) {
  if (idx == n) {
    ans[cnt++] = num;
    return;
  }
  for (int i = 0; i < 10; ++ i) {
    if (isprime(num*10+i)) {
      dfs(idx+1, num*10+i);
    }
  }
}

void solve() {
  cnt = 0;
  dfs(0, 0);
  sort(ans, ans+cnt);
  for (int i = 0; i < cnt; ++ i) {
    printf("%d\n", ans[i]);
  }
}

int main() {
  char *HOME = getenv("HOME");
  if (strcmp(HOME, "/home/atupal") != 0) {
    freopen("sprime.in", "r", stdin);
    freopen("sprime.out","w", stdout);
  }
  scanf("%d", &n);
  solve();

  return 0;
}

