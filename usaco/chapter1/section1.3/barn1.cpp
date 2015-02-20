/*
ID:atupal1
PROG:barn1
LANG:C++11
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 201;
int m, s, c;
int map[maxn];

int main() {
  freopen("barn1.in", "r", stdin);
  freopen("barn1.out","w", stdout);
  scanf("%d %d %d", &m, &s, &c);
  for (int i = 0; i < c; ++ i) {
    scanf("%d", map+i);
  }
  sort(map, map+c);
  for (int i = 1; i < c; ++ i) {
    map[i-1] = map[i] - map[i-1] - 1;
  }
  sort(map, map+c-1);
  int ans = c;
  for (int i = 0; i < c-m; ++ i) {
    ans += map[i];
  }
  printf("%d\n", ans);

  return 0;
}

