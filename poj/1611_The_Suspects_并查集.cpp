/**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 30010;
int n, m;
int p[maxn];
int rank[maxn];

void makeset(int x) {
  p[x] = x;
  rank[x] = 0;
}

int find(int x) {
  if (x != p[x]) {
    p[x] = find(p[x]);
  }
  return p[x];
}

void link(int x, int y) {
  if (rank[x] > rank[y]) {
    p[y] = x;
  } else {
    p[x] = y;
    if (rank[x] == rank[y]) {
      ++ rank[y];
    }
  }
}

int solve() {
  scanf("%d %d", &n, &m);
  if (n + m == 0) return 0;
  memset(p, -1, sizeof(p));
  memset(rank, -1, sizeof(rank));
  makeset(0);
  int k, xhead, x;
  for (int i = 0; i < m; ++ i) {
    scanf("%d", &k);
    if (not k) continue;
    scanf("%d", &xhead);
    if (p[xhead] == -1) {
      makeset(xhead);
    }
    for (int j = 0; j < k-1; ++ j) {
      scanf("%d", &x);
      if (p[x] != -1) {
        link(find(x), find(xhead));
      } else {
        makeset(x);
        link(find(x), find(xhead));
      }
    }
  }
  int ans = 1;
  int phead = find(0);
  for (int i = 1; i < n; ++ i) {
    if (p[i] != -1 and find(i) == phead) {
      ++ ans;
    }
  }
  printf("%d\n", ans);
  return 1;
}

int main() {
  while(solve());
  return 0;
}
