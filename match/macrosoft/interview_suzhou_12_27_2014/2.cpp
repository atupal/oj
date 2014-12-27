#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 100010;
int n, k;
int d[maxn];

int get(long long t) {
  int cnt = 0;
  long long T = 0;
  for (int i = 0; i < n; ++ i) {
    T += t;
    if (T > d[i]) {
      ++ cnt;
      T -= (long long)d[i];
    } else {
      T = 0L;
    }
  }
  if (cnt > n/2) return 1;
  return 0;
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++ i) {
    scanf("%d", d+i);
  }
  int low = 0, high = maxn;
  while (low < high) {
    int mid = (low + high) >> 1;
    if (get(mid)) {
      high = mid;
    } else {
      low = mid+1;
    }
  }
  printf("%d\n", high);

  return 0;
}
