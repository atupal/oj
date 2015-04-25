#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
using namespace std;

const int maxn = 100010;
int n;
int color[maxn];
vector<int> joint[maxn];
int root;

int dfs(int root) {
  int ret = 0;
  return ret;
}

void input() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++ i) {
    joint[i].clear();
  }
  int x, y;
  for (int i =0; i < n-1; ++ i) {
    scanf("%d %d", &x, &y);
    joint[x].push_back(y);
    joint[y].push_back(x);
  }
}

void solve() {
  memset(color, 0, sizeof(color));
  int q;
  scanf("%d", &q);
  int ans = 1;
  for (int i = 0; i < q; ++ i) {
    int q, x, y;
    scanf("%d", &q);
    if (q == 1) {
      printf("%d\n", ans);
    } else {
      scanf("%d %d", &x, &y);

      if (color[x] == y) continue;

      for (int j = 0; j < (int)joint[x].size(); ++ j) {


        if (color[ joint[x][j] ] == color[x]) {
          //printf("+: %d -> %d\n", x, joint[x][j]);
          ans += 1;
        } else if ( color[ joint[x][j] ]  == y) {
          //printf("-: %d -> %d\n", x, joint[x][j]);
          ans -= 1;
        }
      }

      color[x] = y;

    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int c = 1; c <= T; ++ c) {
    printf("Case #%d:\n", c);
    input();
    solve();
  }
  return 0;
}

