#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
int p[] = {2, 3, 5, 7, 11, 13, 17, 19};
const int maxn = (1<<8);
int cache[110000];
long long cnt[maxn+3];

#define hash(x) (cache[x] != -1 ? cache[x] : _hash(x))
inline
int _hash(int x) {
  int xx = x;
  int ret = 0;
  for (int i = 0; i < 8 && x; ++ i) {
    int flag = 0;
    while (x && x % p[i] == 0) {
      x /= p[i];
      flag = 1;
    }
    if (flag)
      ret = ret | (1<<i);
  }
  return cache[xx] = ret;
}

void solve() {
  memset(cnt, 0, sizeof(cnt));
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    int x;
    scanf("%d", &x);
    ++ cnt[hash(x)];
  }

  long long ans = 0;
  for (int i = 0; i <= maxn; ++ i) {
    for (int j = i+1; j <= maxn; ++ j) {
      for (int k = j+1; k <=maxn; ++ k) {
        if ( (!(i&j) && !(j&k) && !(i&k)) || 
            ((i&j) && (j&k) && (i&k)) ) {
          ans += cnt[i] * cnt[j] * cnt[k];
        }
      }
    }
  }

  for (int i = 0; i <= maxn; ++ i) if (cnt[i] >= 3){
    ans += cnt[i]*(cnt[i]-1)*(cnt[i]-2)/6;
  }

  for (int i = 0; i <= maxn; ++ i) {
    for (int j = 0; j <= maxn; ++ j) {
      if (j != i && cnt[i] >= 2 && (i&j)) {
        ans += cnt[i]*(cnt[i]-1)/2 * cnt[j];
      }
    }
  }
  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  memset(cache, -1, sizeof(cache));
  cache[1] = 0;
  while (t--) {
    solve();
  }
  return 0;
}
