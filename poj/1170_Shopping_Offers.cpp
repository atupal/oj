#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dp(i, j) (memo[i][j] != -1 ? memo[i][j] : _dp(i,j))

const int maxn = 11;

struct product {
  int code;
  int price;
  int cnt;
};

struct rule {
  int num;
  int codes[maxn];
  int cnts[maxn];
  int reduce;
};

int np;
int nr;
struct product p[maxn];
struct rule r[100];
int ind[1000];

//int memo[9765625][26];
int memo[10000][26];
//int pre1[100000][26];
//int pre2[100000][26];
//int pre3[100000][26];

void input() {
  memset(ind, -1, sizeof(ind));
  //memset(pre1, -1, sizeof(pre1));
  //memset(pre2, -1, sizeof(pre2));
  //memset(pre3, -1, sizeof(pre3));
  scanf("%d", &np);
  for (int i = 0; i < np; ++ i) {
    scanf("%d %d %d", &p[i].code, &p[i].cnt, &p[i].price);
    ind[p[i].code] = i;
  }
  scanf("%d", &nr);
  for (int i = 0; i < nr; ++ i) {
    scanf("%d", &r[i].num);
    for (int j = 0; j < r[i].num; ++ j) {
      scanf("%d %d", r[i].codes+j, r[i].cnts+j);
    }
    scanf("%d", &r[i].reduce);
  }

  memset(memo, -1, sizeof(memo));
}

//int mask[] = {1, 25, 625, 15625, 390625, 9765625, 244140625};
//int mask[] = {1, 10, 100, 1000, 10000};
int mask[] = {1, 6, 36, 216, 1296};
int _dp(int x, int sum) {
  int min = 0;
  int now = 0;
  int cnt[maxn];
  for (int i = 0; i < np; ++ i) {
    cnt[i] = x / mask[i] % mask[1];
    min += cnt[i] * p[i].price;
    now += cnt[i];
  }

  int tmp;
  for (int i = 0; i < nr; ++ i) {
    for (int j = 1; j <= 1; ++ j) {
      int minus = 0;
      int xx = x;
      int money = 0;
      for (int k = 0; k < r[i].num; ++ k) {
        int index = ind[r[i].codes[k]];
        tmp = j * r[i].cnts[k] - cnt[index];
        minus += tmp > 0 ? tmp : 0;
        xx -= mask[index] * ( tmp > 0 ? cnt[index] : j * r[i].cnts[k] );
        //money += ( tmp > 0 ? 0 : -tmp ) * p[index].price + j * r[i].reduce;
        if (minus + now > sum) {
          goto flag1;
        }
      }

      money = j * r[i].reduce;
      tmp = dp(xx, sum - minus) + money;
      if (tmp < min) {
        min = tmp;
        //pre1[x][sum] = xx;
        //pre2[x][sum] = sum - minus;
        //pre3[x][sum] = i * 100 + j;
      }
    }
flag1:;
  }

  return memo[x][sum] = min;
}

void solve() {
  int ans;
  int x = 0;
  for (int i = 0; i < np; ++ i) {
    x += mask[i] * p[i].cnt;
  }

  ans = dp(x, 25);
  printf("%d\n", ans);

  //int x1, x2, x3;
  //x1 = pre1[x][25];
  //x2 = pre2[x][25];
  //x3 = pre3[x][25];
  //while (x1 != -1) {
  //  printf("rule %d : %d\n", x3 / 100 + 1, x3 % 100);
  //  int t1=x1,t2=x2;
  //  x1 = pre1[t1][t2];
  //  x2 = pre2[t1][t2];
  //  x3 = pre3[t1][t2];
  //}

}

int main() {
  input();
  solve();

  return 0;
}
