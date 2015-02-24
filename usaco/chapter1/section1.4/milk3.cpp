/*
ID:atupal1
PROB:milk3
LANG:C++11
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define triple(a, b, c) ( make_pair(a, make_pair(b, c)) )
#define first(x) ( x.first )
#define second(x) ( x.first.first )
#define third(x) ( x.first.second )

int A, B, C;
map<pair<int, pair<int, int> >, int> vis;
int ans[10000];
int cnt;

inline
int min(int a, int b) {
  return a < b ? a : b;
}
inline
int max(int a, int b) {
  return a > b ? a : b;
}

/*
   pour a -> b
 */
void pour(int &a, int &b, int A, int B) {
  int ta = a;
  int tb = b;
  b = min(B, ta+tb);
  a = max(0, ta-(B-tb) );
}


#define proc(x, y, X, Y) \
  ta = a; tb = b; tc = c; \
  pour(x, y, X, Y); \
  dfs(ta, tb, tc);

void dfs(int a, int b, int c) {
  if (vis[triple(a, b, c)]) return;
  vis[triple(a, b, c)] = 1;
  if (a == 0) {
    ans[cnt++] = c;
  }
  int ta, tb, tc;
  proc(ta, tb, A, B);
  proc(ta, tc, A, C);
  proc(tb, ta, B, A);
  proc(tb, tc, B, C);
  proc(tc, ta, C, A);
  proc(tc, tb, C, B);
}

void solve() {
  cnt = 0;
  dfs(0, 0, C);
  sort(ans, ans+cnt);
  cnt = unique(ans, ans+cnt) - ans;
  for (int i = 0; i < cnt-1; ++ i) {
    printf("%d ", ans[i]);
  }
  printf("%d\n", ans[cnt-1]);
}

int main() {
  char *HOME = getenv("HOME");
  if (strcmp(HOME, "/home/atupal") != 0) {
    freopen("milk3.in", "r", stdin);
    freopen("milk3.out","w", stdout);
  }

  scanf("%d %d %d", &A, &B, &C);
  solve();

  return 0;
}

