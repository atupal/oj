#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

int l, n;
int *d;

void input() {
  free(d);
  scanf("%d%d", &l, &n);
  d = (int *) malloc (sizeof(int) * n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d", d+i);
  }
}

void solve() {
  int minT = 0, maxT = 0;
  for (int i = 0; i < n; ++ i) {
    minT = max(minT, min(d[i], l-d[i]));
    maxT = max(maxT, max(d[i], l-d[i]));
  }
  printf("%d %d\n", minT, maxT);

}

int main() {
  int t;
  scanf("%d", &t);
  while (t --) {
    input();
    solve();
  }
  return 0;
}
