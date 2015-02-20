#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;


const int maxn = 2e5+10;
typedef long long int64;
int64 n;
int b[maxn];

void solve() {
  sort(b,b+n);
  int max = b[n-1] - b[0];
  printf("%d ", max);
  int64 l = 0, r = n-1;
  while (l<n-1 && b[l+1]==b[l]) ++ l;
  while (r && b[r-1]==b[r]) --r;
  if (r <= l) {
    printf("%lld\n", n*(n-1)/2);

  } else {
    printf("%lld\n", (l+1)*(n-r));
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%lld", &n);
    for (int i = 0; i < n; ++ i) {
      scanf("%d", b+i);
    }
    solve();
  }
  return 0;
}
