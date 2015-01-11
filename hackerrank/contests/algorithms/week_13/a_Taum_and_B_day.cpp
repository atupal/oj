#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define min(a, b) ( (a)<(b)?(a):(b) )

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    long long b, w, x, y, z;
    long long ans = 0;
    scanf("%lld%lld%lld%lld%lld", &b, &w, &x, &y, &z);
    ans = min(x,y+z)*b+min(y,x+z)*w;
    printf("%lld\n", ans);
  }
  return 0;
}
