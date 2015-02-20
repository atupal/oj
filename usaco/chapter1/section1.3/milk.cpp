/*
ID: atupal1
PROG: milk
LANG: C++11
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = (int)1e5+1;

ll n;
int m;
struct milk {
  ll price;
  ll amount;
} milks[maxn];

int cmp(milk a, milk b) {
  return a.price < b.price;
}

int main() {
  freopen("milk.out", "w", stdout);
  freopen("milk.in", "r", stdin);
  scanf("%lld %d", &n, &m);
  for (int i = 0; i < m; ++ i) {
    scanf("%lld %lld", &milks[i].price, &milks[i].amount);
  }
  sort(milks, milks+m, cmp);
  ll s = 0;
  ll ans = 0;
  for (int i = 0; i < m; ++ i) {
    if (s + milks[i].amount < n) {
      s += milks[i].amount;
      ans += milks[i].amount * milks[i].price;
    } else {
      ans += milks[i].price * (n-s);
      break;
    }
  }
  printf("%lld\n", ans);

  return 0;
}

