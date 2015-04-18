#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

const int maxn = (int) 2*(1e6)+10;
ll ans;
ll n;
ll primes[maxn];

void solve() {
  memset(primes, 0, sizeof(primes));
  ll b = (ll) sqrt(maxn)+1L;
  b = maxn-1;
  for (ll i = 2; i <= b; ++ i) {
    if (!primes[i]) {
      for (int c = i*2; c < maxn; c += i) {
        ll tmp = c;
        while (tmp%i == 0) {
          primes[c] += i;
          tmp /= i;
        }
      }
      primes[i] = i;
    }
  }

  //for (int i = 2; i < 100; ++ i) {
    //printf("%d -> %lld\n", i, primes[i]);
  //}


  int t;
  scanf("%d", &t);
  ans = 0;
  for (int i = 0; i < t; ++ i) {
    scanf("%lld", &n);
    ans += primes[n];
  }
  printf("%lld\n", ans);
}

int main() {
  solve();

  return 0;
}
