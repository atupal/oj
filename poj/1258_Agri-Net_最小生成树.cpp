#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INF=1000000;
const int maxn = 101;
int n; 
int g[maxn][maxn];

int clostes[maxn];
int lowcost[maxn];

void solve() {
  // prime
  int ans = 0;
  memset(lowcost, 0, sizeof(lowcost));
  for (int i = 0; i < n; ++ i) {
    clostes[i] = 0;
    lowcost[i] = g[0][i];
  }
  for (int i = 0; i < n-1; ++ i) {
    int min = INF;
    int min_one = 0;
    for (int j = 0; j < n; ++ j) {
      if ( lowcost[j] && lowcost[j] < min) {
        min = lowcost[j];
        min_one = j;
      }
    }
    ans += min;
    lowcost[min_one] = 0;
    for (int j = 0; j < n; ++ j) {
      if (g[min_one][j] < lowcost[j]) {
        lowcost[j] = g[min_one][j];
        clostes[j] = min_one;
      }
    }
  }

  printf("%d\n", ans);
}

int main() {
  while (scanf("%d", &n) != EOF) {
    for (int i = 0; i < n; ++ i) {
      for (int j = 0; j < n; ++ j) {
        scanf("%d", g[i]+j);
      }
    }
    solve();
  }

  return 0;
}
