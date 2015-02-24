/*
ID:atupal1
PROB:ariprog
LANG:C++11
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

const int maxn = 251;
int n, m;
int map[maxn*maxn*2];
vector<int> s;

void solve() {
  const int max = m*m*2;
  int ans = 0;
  for (int i = 0; i <= max; ++ i) {
    if (map[i]) {
      s.push_back(i);
    }
  }

  for (int d = 1; d <= max/(n-1)+1; ++ d) {
    for (int i = 0; i < (int)s.size(); ++ i) {
      int cnt = n;
      int idx = s[i];
      int flag = 1;
      while (cnt--) {
        if (idx > max || map[idx] == 0) {
          flag = 0;
          break;
        }
        idx += d;
      }
      if (flag) {
        ans = 1;
        printf("%d %d\n", s[i], d);
      }

    }
  }


  if (!ans) {
    printf("NONE\n");
  }

}

int main() {
  freopen("ariprog.in", "r", stdin);
  freopen("ariprog.out", "w", stdout);
  scanf("%d %d", &n, &m);
  memset(map, 0, sizeof(map));
  for (int i = 0; i <= m; ++ i) {
    for (int j = 0; j <= m; ++ j) {
      map[ i*i + j*j ] = 1;
    }
  }
  solve();

  return 0;
}

