#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <map>

using namespace std;

typedef unsigned long long int64;

const int maxn = 110000;
char s[maxn];
int n;
int64 cnt[4];
int64 p[4];
int ans[4];
int a[maxn];
map <int64, bool> vis;

inline int64 min(int64 a, int64 b) {
  return a < b ? a : b;
}

inline int64 getmin() {
  return min( min( cnt[0], cnt[1] ) , min(cnt[2], cnt[3]) );
}

inline int isvis(int64 idx) {
  int64 tmp = idx;
  for (int x = 0; x < 4; ++ x) tmp += p[x]*cnt[x];
  if (!vis[tmp]) {
    vis[tmp] = 1;
    return 0;
  }
  return 1;
}

void  dfs(int64 idx) {
  if (idx > (int64)n) {
    /*
    for (int x = 1; x <= n; ++ x) {
      printf("%d", a[x]);
    }
    printf(": ");
    */
    int64 m = getmin();
    for (int i = 0; i < 4; ++ i) {
      if (cnt[i] == m) {
        ans[i] = 1;
        //printf("%d", i);
      }
    }
    //printf("\n");
    return;
  }
  if (s[idx] == -1) {
    int64 m = getmin();
    for (int i = 0; i < 4; ++ i) {
      if (m == cnt[i]) {
        ++ cnt[i];
        a[idx] = i;
        if (!isvis(idx)) {
          dfs(idx+1);
        } 
        -- cnt[i];
      }
    }
  } else {
    ++ cnt[ (int)s[idx] ];
    a[idx] = s[idx];
    if (!isvis(idx)) {
      dfs(idx+1);
    } 
    -- cnt[ (int)s[idx] ];
  }
}

void solve() {
  memset(ans, 0, sizeof(ans));
  memset(cnt, 0, sizeof(cnt));
  vis.clear();
  dfs(1);
}

int main() {
  int t;
  char out[4][50] = {"Go Kart Racing", "Horse Riding", "Rugby", "Snow Polo"};
  scanf("%d", &t);
  p[0] = (int64)10000;
  for (int i = 1; i < 4; ++ i) {
    p[i] = p[i-1]*(int64)10000;
  }
  for (int c = 0; c < t; ++ c) {
    scanf("%d", &n);
    scanf("%s", s+1);
    for (int i = 1; i <= n; ++ i) {
      if (s[i] == '?') {
        s[i] = -1;
      } else {
        for (int x = 0; x < 4; ++ x) {
          if (out[x][0] == s[i]) {
            s[i] = x;
          }
        }
      }
    }
    //printf("%d:%d\n", c,n);
    solve();
    for (int i = 0; i < 4; ++ i) {
      if (ans[i]) {
        printf("%s\n", out[i]);
      }
    }
    if (c < t-1) printf("\n");
  }
}

