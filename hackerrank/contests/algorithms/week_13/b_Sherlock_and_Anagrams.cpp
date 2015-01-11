#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>
#include <math.h>

using namespace std;

map<string, int> counter;


char s[200];

void solve() {
  counter.clear();
  int n = (int) strlen(s);
  for (int i = 0; i < n; ++ i) {
    for (int j = i; j < n; ++ j) {
      int cnt[30];
      memset(cnt, 0, sizeof(cnt));
      for (int x = i; x <= j; ++ x) {
        ++ cnt[ s[x]-'a' ];
      }
      char sum[256];
      sum[0] = 0;
      for (int x = 0; x < 26; ++ x) {
        sprintf(sum+strlen(sum), "(%d,%d)", x, cnt[x]);
      }
      if (counter[sum]) {
        counter[sum] += 1;
      } else {
        counter[sum] = 1;
      }
    }
  }

  int ans = 0;
  for (map<string, int>::iterator it = counter.begin(); it != counter.end(); ++ it) {
    if ( it->second > 1) {
      ans += it->second * (it->second-1)/2;
    }
  }
  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  for (;t--;) {
    scanf("%s", s);
    solve();
  }

  return 0;
}
