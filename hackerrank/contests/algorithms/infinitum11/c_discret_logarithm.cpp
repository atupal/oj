#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <math.h>
using namespace std;
typedef long long ll;

ll gcdEx(ll a, ll b, ll *x, ll *y) {
  if(b==0) {
    *x = 1ll,*y = 0ll;
    return a;
  } else {
    ll r = gcdEx(b, a%b, x, y);
    ll t = *x;
    *x = *y;
    *y = t - a/b * *y;
    return r;
  }
}

ll pow_mod(ll a, ll i, ll n) {
  if (i == 0) return 1;
  ll temp = pow_mod(a, i>>1, n);
  temp = temp*temp%n;
  if (i&1) temp = (ll) temp*a%n;
  return temp;
}

ll discreate_log(ll x, ll n, ll m) {
  map<ll, ll> rec;
  ll s = (ll) (sqrt((double)m));
  for (; (ll) s * s <= m; ) s++;
  ll cur = 1L;
  for (ll i = 0; i < s; ++ i) {
    if (!rec[cur])
      rec[cur] = i;
    cur = cur * x % m;
  }
  ll mul = cur;
  cur = 1L;

  ll more;

  ll xx, yy;
  gcdEx(m, x, &xx, &yy);
  while (yy < 0) yy += m;
  more = n;

  for (ll i = 0; i < s; ++ i) {
    // fuck bug! 欧拉方法求模逆元会有点 bug
    //more = (ll) n* pow_mod(cur, m-2, m) % m;
    if (rec.count(more)) {
      return i * s + rec[more];
    }
    //cur = cur * mul % m;
    more = more*pow_mod(yy, s, m)%m;
  }
  return -1;
}

int main() {
  //printf("%lld\n", pow_mod(233529, 72891, 329746));
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++ i) {
    //int a, b , g;
    ll x, n, m;
    scanf("%lld %lld %lld", &x, &n, &m);
    ll a = discreate_log(x, n, m);
    printf("%lld\n", a);
  }

  return 0;
}

