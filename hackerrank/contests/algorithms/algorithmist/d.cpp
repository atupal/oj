#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 1e4+10;
char s[maxn];
int n;
int cnt[4];
int ans[4];

inline
int min(int a, int b) {
  return a < b ? a : b;
}

inline
int getmin() {
  return min( min(cnt[0], cnt[1]), min(cnt[2], cnt[3]) );
}


int bug[maxn];
void solve() {
  memset(ans, 0 ,sizeof(ans));
  int a[4];
  for (int i = 0; i < 4; ++ i) 
  for (int j = 0; j < 4; ++ j)
  for (int k = 0; k < 4; ++ k)
  for (int l = 0; l < 4; ++ l) if (i != j && i != k && i != l && j != k && j != l && k != l) {
    a[0] = i, a[1] = j, a[2] = k, a[3] = l;
    /*
    for (int hehe = 0; hehe < 4; ++ hehe) {
      printf("%d", a[hehe]);
    }
    printf(": ");
    */
    memset(cnt, 0, sizeof(cnt));
    for (int x = 1; x <= n; ++ x) {
      int m = getmin();
      char ju = s[x];
      if (ju == '?') {
        for (int y = 0; y < 4; ++ y) {
          if (cnt[a[y]] == m) {
            ++ cnt[a[y]];
            bug[x] = a[y];
            break;
          }
        }
      } else if (ju == 'G') {
        bug[x] = 0;
        ++ cnt[0];
      } else if (ju == 'H') {
        bug[x] = 1;
        ++ cnt[1];
      } else if (ju == 'R') {
        bug[x] = 2;
        ++ cnt[2];
      } else if (ju == 'S') {
        bug[x] = 3;
        ++ cnt[3];
      }
    }

    /*
    for (int x = 1; x <= n; ++ x) {
      printf("%d", bug[x]);
    }
    printf("\n");
    */

    int m = getmin();
    for (int x = 0; x < 4; ++ x) {
      if (cnt[x] == m) {
        ans[x] = 1;
      }
    }

  }
}

int main() {
  int t;
  scanf("%d", &t);
  char out[4][maxn] = {"Go Kart Racing", "Horse Riding", "Rugby", "Snow Polo"};
  for (int c = 0; c < t; ++ c) {
    scanf("%d", &n);
    scanf("%s", s+1);
    solve();
    //printf("%d:%d\n", c, n);
    for (int i = 0; i < 4; ++ i) {
      if (ans[i]) {
        printf("%s\n", out[i]);
      }
    }


    if (c < t-1) printf("\n");
  }
}

