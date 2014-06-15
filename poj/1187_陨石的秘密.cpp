#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 11380
#define dp(i,j,k,d,t) (mo[i][j][k][d][t] != -1 ? mo[i][j][k][d][t] : _dp(i,j,k,d,t))
#define dp_sum(i,j,k,d) (mo_sum[i][j][k][d] != -1 ? mo_sum[i][j][k][d] : _dp_sum(i,j,k,d))

const int maxn = 11;
int l[3];
int d;

int mo[maxn][maxn][maxn][maxn*3][3];
int mo_sum[maxn][maxn][maxn][maxn*3];
int A[maxn];

int _dp_sum(int l1, int l2, int l3, int deep);

int _dp(int l1, int l2, int l3, int deep, int color) {
  printf("%d %d %d : %d, %d\n", l1, l2, l3, deep, color);
  int sum = 0;
  if (color == 0) {
    for (int i = deep; i <= l1; ++ i) {
      sum += dp_sum(l1-i, l2, l3, deep) * dp(i-1, 0, 0, deep-1, 0);
    }
  } else if(color == 1) {
    for (int i = 0; i <= l1; ++ i) {
      for (int j = deep - i < 0 ? 0 : deep - i; j <= l2; ++ j) {
        sum += dp_sum(l1-i, l2-j, l3, deep) * (dp(i, j, 0, deep-1, 0) + dp(i, j, 0, deep-1, 1));
      }
    }
  } else {
    for (int i = 0; i <= l1; ++ i) {
      for (int j = 0; j <= l2; ++ j) {
        for (int k = deep-i-j < 0 ? 0 : deep-i-j; k <= l3; ++ k) {
          sum += dp_sum(l1-i, l2-j, l3-k, deep) * (dp(i,j,k,deep-1,0)
              + dp(i,j,k,deep-1,1)
              + dp(i,j,k,deep-1,2)
              );
        }
      }
    }
  }

  sum += sum;
  //sum /= A[l1];
  //sum /= A[l2];
  //sum /= A[l3];
  sum %= MOD;

  return mo[l1][l2][l3][deep][color] = sum;
}

int _dp_sum(int l1, int l2, int l3, int deep) {
  int sum = 0;
  for (int d = 1; d <= deep; ++ d) {
    for (int i = 0; i < 3; ++ i) {
      sum += dp(l1, l2, l3, d, i);
    }
  }
  sum %= MOD;

  return mo_sum[l1][l2][l3][deep] = sum;
}

void solve() {
  memset(mo, -1, sizeof(mo));
  memset(mo_sum, -1, sizeof(mo_sum));
  A[0] = 1;
  for (int i = 1; i <= 10; ++ i) {
    A[i] = A[i-1] * i;
  }

  for (int i = 0; i < maxn * 3; ++ i) {
    mo[0][0][0][i][0] = 1;
    mo[0][0][0][i][1] = 1;
    mo[0][0][0][i][2] = 1;
  }

  for (int i = 0; i < maxn; ++ i) {
    for (int j = 0; j < maxn; ++ j) {
      for (int k = 0; k < maxn; ++ k) {
        mo[i][j][k][0][0] = 0;
        mo[i][j][k][0][1] = 0;
        mo[i][j][k][0][2] = 0;
      }
    }
  }
  mo[0][0][0][0][0] = 1;
  mo[0][0][0][0][1] = 1;
  mo[0][0][0][0][2] = 1;

  printf("%d\n", dp(10, 0, 0, 1, 0));
  return;

  printf("%d\n", (MOD + dp_sum(l[0], l[1], l[2], d) - dp_sum(l[0], l[1], l[2], d-1)) % MOD);
}

int main() {
  //scanf("%d %d %d %d", l, l+1, l+2, &d);
  solve();

  return 0;
}
