#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

const int maxn = 500010;
int n;
int a[maxn];
int primes[maxn];

void solve() {
  int ans = 0;
  for (int i = 1; i < (1<<n); ++ i) {
    vector<int> s;
    s.clear();
    for (int j = 0; j < n; ++ j) {
      if ((i>>j)&1) {
        s.push_back(a[j]);
      }
    }


    int cnt = s.size();

    for (int x = 0; x < cnt; ++ x) {
      for (int y = x+1; y < cnt; ++ y) {
        int a = s[x], b = s[y];
        if (a < b) {
          int tmp = b;
          b = a;
          a = tmp;
        }
        if (a == b) goto here;
        if (a%b == 0 && !primes[a/b]) {
          goto here;
        }
      }
    }
    
    if (cnt > ans) {
      ans = cnt;
    }

here:;



  }

  printf("%d\n", ans);
}

void init() {
  memset(primes, 0, sizeof(primes));
  int b = (int) sqrt(maxn)+1L;
  b = maxn-1;
  for (int i = 2; i <= b; ++ i) {
    if (!primes[i]) {
      for (int c = i*2; c < maxn; c += i) {
        primes[c] = 1;
      }
      primes[i] = 0;
    }
  }
}


int main() {
  int T;
  init();

  scanf("%d", &T);

  for (int i = 1; i <= T; ++ i) {
    scanf("%d", &n);
    for (int j = 0; j < n; ++ j) {
      scanf("%d", a+j);
    }
    printf("Case #%d: ", i);
    solve();
  }

  return 0;
}

