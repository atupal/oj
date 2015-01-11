#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 1e5+10;
int n;
char s[256];
int a[maxn];

int order[maxn];
int pointer = 0;
void dfs(int vertex, int depth) {
  if (vertex > 32) return;
  printf("%d ", depth);

  order[ pointer ] = depth;
  pointer ++;
  dfs( vertex<<1, depth+1 );
  dfs( vertex<<1|1, depth+1 );
}

void test() {
  dfs(1, 0);
  printf("\n");
  for (int i = 0; i < 32; ++ i) {
    printf("%d ", order[i]);
  }
}

typedef long long int64;
const int64 MOD = 1e9+7;

inline
void add(int64 &a, int64 b) {
  a += b;
  a %= MOD;
}

/*
int64 memo[maxn][200+10];
inline
int64 dp(int pos, int val) {
  if (val < 0) {
    return 0L;
  }

  int64 &ret = memo[pos][val];
  if (ret != -1) return ret;


  if (val == 0) {
    if (pos != 1) ret = 0;
    return ret;
  }
  
  ret = 0L;
  if ( a[pos] == -1 || a[pos] == val) {
    add(ret, dp(pos-1, val));
    add(ret, dp(pos-1, val-1));
    add(ret, dp(pos-1, val+1));
  }

  return ret;
}
*/

int MAX;


int64 pre[maxn];
int64 now[maxn];

void solve() {
  //memset(memo, -1, sizeof(memo));
  memset(pre, 0, sizeof(pre));
  //for (int i = 0; i < maxn; ++ i) {
    //memo[1][i] = 0;
  //}
  //memo[1][0] = 1;
  pre[0] = 1;
  if ( a[1] > 0) {
    printf("0\n");
    return;
  } 

  for (int i = 2; i <= n; ++ i) {
    memset(now, 0, sizeof(now));
    for (int j = 1; j <= MAX; ++ j) {
      if ( a[i] == -1 || a[i] == j) {
        add(now[j], pre[j]);
        if ((j-1) || i==2) add(now[j], pre[j-1]);
        add(now[j], pre[j+1]);
      } else {
        now[j] = 0L;
      }
    }
    memcpy(pre, now, sizeof(now));
  }

  int64 ans = 0;
  if ( a[n] == -1) {
    for (int i = 0; i <= MAX; ++ i) {
      //ans += dp(n, i);
      ans += now[i];
      //printf("%d - %lld\n", i, now[i]);
    }
  } else {
    //ans = dp(n, a[n]);
    ans = now[a[n]];
  }
  printf("%lld\n", ans);
}

int main() {
  MAX = maxn-2;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++ i) {
    scanf("%s", s);
    if ( s[0] == '?') {
      a[i] = -1;
    } else {
      a[i] = atoi(s);
    }
  }

  solve();

  return 0;
}
