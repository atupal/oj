#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lowbit(x) ((x)&(-(x)))

const int maxn = 2e5+10;
typedef long long int64;

int n, q;
int64 a[maxn];
int64 sum[maxn];


int main() {
  scanf("%d %d", &n, &q);
  sum[0] = 0;
  for (int i = 1; i <= n; ++ i) {
    scanf("%lld", a+i);
    sum[i] = sum[i-1]+a[i];
  }

  for (int i = 0; i < q; ++ i) {
    int op, l, r;
    scanf("%d %d %d", &op, &l, &r);
    if (op == 1) {

      for (int x = l; x < r; x += 2) {
        a[x] ^= a[x+1] ^= a[x] ^= a[x+1];
        sum[x] = sum[x-1]+a[x];
      }

    } else {
      printf("%lld\n", sum[r]-sum[l-1]);
    }
  }

  return 0;
}
