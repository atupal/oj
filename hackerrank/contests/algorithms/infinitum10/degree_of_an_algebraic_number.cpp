#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>


typedef long long ll;

using namespace std;

int A[101];

inline
void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d", A+i);
  }

  for (int i = 0; i < n; ++ i) {
    int bd = (int) sqrt(A[i]) + 1;
    for (int a = bd; a > 1; -- a) {
      if (A[i] % (a*a) == 0) {
        A[i] /= a*a;
        break;
      }
    }
  }

  sort(A, A+n);
  ll cnt = unique(A, A+n) - A;
  if (A[0] == 1) {
    cnt -= 1;
  }
  printf("%lld\n", 1ll<<cnt);

}

int main() {
  int t;
  scanf("%d", &t);
  for (;t--;) {
    solve();
  }

  return 0;
}

