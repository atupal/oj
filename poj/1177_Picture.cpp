#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 5001;
int n;
int lef[maxn], rig[maxn], low[maxn], hig[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d %d %d %d", lef+i, low+i, rig+i, hig+i);
  }

  return 0;
}
