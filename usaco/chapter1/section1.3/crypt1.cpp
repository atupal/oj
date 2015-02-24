/*
ID:atupal1
PROG:crypt1
LANG:C++11
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int n;
vector<int> s;
int d[10];
int p[10];
int ans;

void dfs(int idx, int num) {
  p[idx] = num;
  if (idx == 5) {
    int ret = (p[1]*100+p[2]*10+p[3])*(num*10+p[4]);
    int p1 = (p[1]*100+p[2]*10+p[3])*p[4];
    int p2 = (p[1]*100+p[2]*10+p[3])*num;
    if ( ret < 10000 && p1 < 1000) {
      if ( d[p1%10] && d[p1/10%10] && d[p1/100] &&
           d[p2%10] && d[p2/10%10] && d[p2/100] &&
           d[ret%10] && d[ret/10%10] && d[ret/100%10] && d[ret/1000]) {
        ans += 1;
      }
    }
    return;
  }
  for (int i = 0; i < (int)s.size(); ++ i) {
    dfs(idx+1, s[i]);
  }
}

void solve() {
  dfs(0, 0);
  printf("%d\n", ans);
}

int main() {
  freopen("crypt1.in", "r", stdin);
  freopen("crypt1.out","w", stdout);
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    int t;
    scanf("%d", &t);
    d[t] = 1;
    s.push_back(t);
  }
  solve();

  return 0;
}

