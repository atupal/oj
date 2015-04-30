#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

typedef unsigned long long u64int;
const int maxn = 60;
int N;
int A[maxn];

u64int memo[14][14][14][14][5];
int init[14][14][14][14][5];

u64int dp(int a, int b, int c, int d, int e) {
  if (init[a][b][c][d][e]) return memo[a][b][c][d][e];
  init[a][b][c][d][e] = 1;
  u64int &ret = memo[a][b][c][d][e];
  ret = 0;

  if (e == 1 && a) {
    for (int i = 1; i <= 4; ++ i) {
      ret += dp(a-1, b, c, d, i);
    }
    ret *= a;
  }
  if (e == 2 && b) {
    for (int i = 1; i <= 4; ++ i) {
      ret += dp(a+1, b-1, c, d, i);
    };
    for (int i = 1; i <= 4; ++ i) {
      ret -= dp(a, b-1, c, d, i);
    }
    ret *= b*2;
  }
  if (e == 3 && c) {
    for (int i = 1; i<= 4; ++ i) {
      ret += dp(a, b+1, c-1, d, i);
    }
    for (int i = 1; i <= 4; ++ i) {
      ret -= dp(a+1, b, c-1, d, i)*2;
    }
    for (int i = 1; i <= 4; ++ i) {
      ret += dp(a, b, c-1, d, i)*2;
    }
    ret *= c*3;
  }
  if (e == 4 && d) {
    for (int i = 1; i <= 4; ++ i) {
      ret += dp(a, b, c+1, d-1, i);
    }
    for (int i = 1; i <= 4; ++ i) {
      ret -= dp(a, b+1, c, d-1, i)*3;
    }
    for (int i = 1; i <= 4; ++ i) {
      ret += dp(a+1, b, c, d-1, i)*3*2;
    }
    for (int i = 1; i <= 4; ++ i) {
      ret -= dp(a, b, c, d-1, i)*3*2;
    }

    ret *= d*4;
  }


  //printf("%d %d %d %d %d -> %llu\n", a, b, c, d, e, ret);

  return ret;
}

void clear() {
  memset(memo, 0, sizeof(memo));
  memset(init, 0, sizeof(init));

  for (int i = 1; i <= 4; ++ i) {
    init[0][0][0][0][i] = 1;
    init[1][0][0][0][i] = 1;
    init[0][1][0][0][i] = 1;
    init[0][0][1][0][i] = 1;
    init[0][0][0][1][i] = 1;
  }
  memo[1][0][0][0][1] = 1;
}

void solve() {
  u64int ans = 0;

  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;

  for (int i = 0; i < maxn; ++ i) {
    if (A[i] == 1) a++;
    if (A[i] == 2) b++;
    if (A[i] == 3) c++;
    if (A[i] == 4) d++;
  }

  for (int i = 1; i <= 4; ++ i) {
    ans += dp(a, b, c, d, i);
  }

  printf("%llu\n", ans);
}

int main() {
  //solve();
  //return 0;
  clear();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++ cas) {
    memset(A, 0, sizeof(A));
    scanf("%d", &N);
    for (int i = 0 ;i < N; ++ i) {
      char s[5];
      scanf("%s", s);
      if (s[0] >= 'A' && s[0] <= 'Z') {
        A[ s[0]-'A'+10 ] ++;
        //A[i] = s[0] - 'A' + 10;
      } else {
        A[ s[0]-'0' ] ++;
        //A[i] = s[0] - '0';
      }
    }
    printf("Case #%d: ", cas);
    solve();
  }

  return 0;
}

