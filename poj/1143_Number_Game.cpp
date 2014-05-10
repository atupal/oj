#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dp(x) (momo[x] != -1 ? momo[x] : is_win(x))

const int maxn = 21;

int T = 0;

int n;
int s[maxn];
int momo[1<<22];
int ans[maxn];

void input() {
  ++ T;
  scanf("%d", &n);
  memset(momo, -1, sizeof(momo));
  memset(s, 0, sizeof(s));
  memset(ans, 0, sizeof(ans));
  if (not n) {
    exit(0);
  }

  for (int i = 0; i < n; ++ i) {
    int tmp;
    scanf("%d", &tmp);
    s[tmp] = 1;
  }

  momo[0] = 0;

}

int deep;
int is_win(int x) {
  int Ans = 0;
  deep += 1;

  int s1[maxn];
  int s2[maxn];
  memset(s1, 0, sizeof(s1));
  memset(s2, 0, sizeof(s2));

  //此处不宜使用位运算代替，因为处于循环内部所以位运算反而会消耗更多的cpu time
  for (int i = 2; i < maxn; ++ i) {
    if (x & (1 << i)) {
      s1[i] = 1;
    }
  }

  for (int i = 2; i < maxn; ++ i) if(s1[i]) {

    memcpy(s2, s1, sizeof(s1));

    for (int k = i; k < maxn; k += i) {
      int tmp;
      for (int j = k; j < maxn; ++ j) {
        tmp = j - k;
        if (tmp != 1 and not s1[tmp]) {
          s2[j] = 0;
        }
      }
    }

    /*
    for (int j = i; j < maxn; ++ j) if (s2[j]) {
      for (int p = 1; p < maxn; ++ p) {
        for (int q = 0; q < maxn; ++ q) {
          for (int r = 2; r < maxn; ++ r) if (not s1[r]) {
            if (j == p * i + q * r) {
              s2[j] = 0;
              goto flag1;
            }
          }
        }
      }
flag1:;
    }
    */


    int xx = 0;
    for (int j = 2; j < maxn; ++ j) if(s2[j]) {
      xx |= (1 << j);
    }

    if (not dp(xx)) {
      if (deep == 1) {
        ans[i] = 1;
      }
      Ans = 1;
    }

  }

  deep -= 1;
  return momo[x] = Ans;
}

int flag;
void solve() {
  int x = 0;
  for (int i = 2; i < maxn; ++ i) {
    if (s[i]) {
      x |= (1 << i);
    }
  }

  deep = 0;
  flag = dp(x);
}

void output() {
  printf("Test Case #%d\n", T);
  if (not flag) {
    printf("There's no winning move.\n\n");
  } else {
    printf("The winning moves are:");
    for (int i = 2; i < maxn; ++ i) {
      if (ans[i])
        printf(" %d", i);
    }
    printf("\n\n");
  }
}

int main() {
  while (1) {
    input();
    solve();
    output();
  }

  return 0;
}
