#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
using namespace std;

typedef long long ll;

const int maxn = (int)2e6+10;
int base[4];
int power[4];
vector<int> primes;
int isprime[maxn];
int *dp;

inline
ll euler(ll n) {
  ll ret = n; 
  ll bd = (ll)sqrt(n) + 1;
  if (bd >= n) bd = n-1;
  for (ll i = 2; i <= bd; ++ i ) {
    if (n%i == 0) {
      ret *= (i-1);
      ret /= i;
      while (n%i==0) {
        n /= i;
      }
    }
  }
  if (n > 1) {
    ret *= (n-1);
    ret /= n;
  }

  return ret;
}

int test(ll n) {
  //n = 216;
  int ans = 0;
  while (n != 1) {
    ans += 1;
    //printf("%lld -> ", n);
    n = euler(n);
  }
  return ans;
}

void fake_solve() {
  ll cnt = 1;
  for (int i = 0; i < 4; ++ i) {
    for (int x = 0; x < power[i]; ++ x) {
      cnt *= base[i];
    }
  }
  printf("%d\n", test(cnt));
}

inline
void solve() {
  map<int, int> fact;
  for (int i = 0; i < 4; ++ i) {
    int tmp = base[i];
    for (__typeof(primes.begin()) iter = primes.begin(); iter != primes.end() && (*iter)*(*iter) <= tmp; ++ iter) {
      int cnt = 0;
      while (tmp%(*iter) == 0) {
        cnt += 1;
        tmp /= *iter;
      }
      fact[*iter] += cnt*power[i];
    }
    if (tmp != 1) {
      fact[tmp] += power[i];
    }
  }

  ll ans = 0;
  for (__typeof(fact.begin()) iter = fact.begin(); iter != fact.end(); ++ iter) {
    //printf("%d %d\n", iter->first, iter->second);
    ans += (ll) (dp[iter->first] * iter->second);
  }
  if (ans && !fact[2]) {
    ans += 1;
  }
  printf("%lld\n", ans);

}


void init() {
  memset(isprime, -1, sizeof(isprime));
  int b = (int) sqrt(maxn);
  for (int i = 2; i <= b; ++ i) {
    if (isprime[i]) {
      for (int c = i*i; c < maxn; c += i) {
        isprime[c] = 0;
      }
    }
  }
  for (int i = 2; i < maxn; ++ i) {
    if (isprime[i]) {
      primes.push_back(i);
    }
  }

  memset(isprime, 0, sizeof(isprime));
  dp = isprime;

  /*
   * 所有的指数最后都分解到 2 的幂,比如 3 的 三次方最后可以由欧拉函数的分解质因数求法规约到 2 的 三次方.
   * 5 的 n 次次方可以规约到 2 的 2n 次方 (因为5-1=2^2)
   * 7 的 n 次次方也可以规约到 2 的 2n 次方,因为 7-1=2*3
   * 而 11 的 n 次方可以规约到 2 的 3n 次方,因为 11-1 = 10 = 2*5, 而 5 是规约到 2 的,所以就是 1+2 =3
   * ...
   * 一次类推,所以用 dp 顺推一下就好了.
   * 最后算全部规约到了 2 的多少次方就需要多少次欧拉函数计算.注意当素因子没有 2 的时候,答案需要加个 1,因为在规约
   * 的过程中会出现 2 .详见 solve 函数.
   * */
  int l = primes.size();
  dp[2] = 1;
  for (int i = 1; i < l; ++ i) {
    int p = primes[i];
    dp[p] = 0;
    int tmp = p-1;
    for (__typeof(primes.begin()) iter = primes.begin(); iter != primes.end() && (*iter)*(*iter) <= tmp; ++ iter) {
      int cnt = 0;
      while (tmp%(*iter) == 0) {
        cnt += 1;
        tmp /= *iter;
      }
      dp[p] += cnt*dp[*iter];
    }
    if (tmp != 1) {
      dp[p] += dp[tmp];
    }
  }

}

int main() {

  init();

  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; ++ i) {
    scanf("%d %d %d %d %d %d %d %d", base, power, base+1, power+1, base+2, power+2, base+3, power+3);
    solve();
  }

  return 0;
}

