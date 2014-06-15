#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


const int maxn = 82;
char s[maxn];
int n;

typedef struct _bignum {
  int pre;
  int b;
  int e;
  void set(int x, int y) {
    pre = x;
    while (x < y and s[x] == '0') {
      ++ x;
    }
    b = x;
    e = y;
  }

  bool operator < (const _bignum& v2) const {
    if (b == -1) return 0;
    if (v2.b == -1) return 1;
    int l1 = e - b + 1;
    int l2 = v2.e - v2.b + 1;
    if (l1 != l2) {
      return l1 < l2;
    } else {
      for (int i = 0; i < l1; ++ i) {
        if (s[b+i] != s[v2.b+i]) {
          return s[b+i] < s[v2.b+i];
        }
      }
    }
    return 0;
  }

  _bignum operator = (const _bignum& v2) {
    b = v2.b;
    e = v2.e;
    pre = v2.pre;
    return v2;
  }


} bignum;

bignum mo[maxn][maxn];

int input() {
  scanf("%s", s);
  if (strcmp(s, "0") == 0)
    return 1;
  n = strlen(s);

  return 0;
}

/*
   dp(x, c): (0, x) 严格升序,总共 c 个部分,的最后一个数的最小值
 */

void out(int, int);
void solve() {
  memset(mo, -1, sizeof(mo));
  for (int i = 0; i <= n; ++ i)  {
    mo[0][i].set(-1, -1);
  }
  for (int i = 0; i < n; ++ i) {
    mo[i][1].set(0, i);
  }

  bignum t;
  for (int i = 1; i < n; ++ i) {
    for (int j = 1; j <= i+1; ++ j) {
      for (int x = 1; x <= i; ++ x) {
        t.set(x, i);
        if(mo[x-1][j-1] < t) {
          mo[i][j] = t;
        }
      }
    }
  }

  int c = 1;
  bignum ans;
  ans.set(0, n-1);
  for (int x = 1; x<=n; ++ x) {
    if (mo[n-1][x]< ans) {
      ans = mo[n-1][x];
      c = x;
    }
  }

  out(n-1, c);
  printf("\n");
}

void out(int x, int c) {
  if (x < 0 or c <= 0) return;
  out(mo[x][c].pre-1, c-1);
  if (mo[x][c].pre-1>=0) printf(",");
  for (int i = mo[x][c].pre; i <= mo[x][c].e; ++ i) {
    printf("%c", s[i]);
  }
}

int main() {
  while (input() == 0) {
    solve();
  }
  return 0;
}
