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
const int MAX = 200000;
const int64 MOD = 1e9+7;
//int64 memo[maxn][MAX+10];
int64 memo[2][MAX+10];

inline
void add(int64 &a, int64 b) {
  a += b;
  a %= MOD;
}

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

void solve() {
  //memset(memo, -1, sizeof(memo));
  memset(memo, 0, sizeof(memo));
  for (int i = 0; i < MAX+10; ++ i) {
    memo[1][i] = 0;
  }
  memo[1][0] = 1;
  if ( a[1] > 0) {
    printf("0\n");
    return;
  } 

  for (int pos = 2; pos <= n; ++ pos) {
    for (int val = 0; val < MAX; ++ val) {
      if (val == 0) {
        memo[pos%2][val] = 0;
        continue;
      }
      
      int64 ret = 0L;
      if ( a[pos] == -1 || a[pos] == val) {
        //add(ret, dp(pos-1, val));
        //add(ret, dp(pos-1, val-1));
        //add(ret, dp(pos-1, val+1));
        add(ret, memo[(pos-1)%2][val]);
        if(val) add(ret, memo[(pos-1)%2][val-1]);
        add(ret, memo[(pos-1)%2][val+1]);
      }
      memo[pos%2][val] = ret;
    }
  }

  int64 ans = 0;
  if (a[n] == -1) {
    for (int i = 0; i < MAX; ++ i) {
      //printf("%d - %lld %lld\n", i, dp(n, i), memo[n][i]);
      //ans += dp(n, i);
      ans += memo[n%2][i];
      ans %= MOD;
    }
  } else {
    //ans = dp(n, a[n]);
    ans = memo[n%2][a[n]];
  }
  printf("%lld\n", ans);
}

int main() {
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
