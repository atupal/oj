#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 1e4+10;
char s[maxn];
int n;

struct node {
  int cnt;
  int id;
};

int cmp(node a, node b) {
  return a.cnt < b.cnt;
}

node sp[4];

int ans[4];
void  dfs(int idx) {
  node so[4];
  if (idx > n) {
    memcpy(so, sp, sizeof(sp));
    sort(so, so+4, cmp);
    int bound = 0;
    while (bound+1<4 && so[bound+1].cnt==so[bound].cnt) ++ bound;
    for (int i = 0; i <= bound; ++ i) {
      ans[ so[i].id ] = 1;
    }
    return;
  }

  if (s[idx] == '?') {
    memcpy(so, sp, sizeof(sp));
    sort(so, so+4, cmp);
    int bound = 0;
    while (bound+1<4 && so[bound+1].cnt==so[bound].cnt) ++ bound;
    for (int i = 0; i <= bound; ++ i) {
      ++ sp[ so[i].id ].cnt;
      dfs(idx+1);
      -- sp[ so[i].id ].cnt;
    }
  } else {
    if ( s[idx] == 'G') {
      ++ sp[0].cnt;
      dfs(idx+1);
      -- sp[0].cnt;
    } else if ( s[idx] == 'H') {
      ++ sp[1].cnt;
      dfs(idx+1);
      -- sp[1].cnt;
    } else if ( s[idx] == 'R') {
      ++ sp[2].cnt;
      dfs(idx+1);
      -- sp[2].cnt;
    } else {
      ++ sp[3].cnt;
      dfs(idx+1);
      -- sp[3].cnt;
    }
  }
}

void solve() {
  memset(sp, 0, sizeof(sp));
  memset(ans, 0, sizeof(ans));
  for (int i= 0; i < 4; ++ i) {
    sp[i].id = i;
    sp[i].cnt = 0;
  }
  dfs(1);
  if (ans[0]) {
    printf("Go Kart Racing\n");
  }
  if (ans[1]) {
    printf("Horse Riding\n");
  }
  if (ans[2]) {
    printf("Rugby\n");
  }
  if (ans[3]) {
    printf("Snow Polo\n");
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    scanf("%s", s+1);
    solve();
    printf("\n");
  }
}

