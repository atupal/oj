/*
ID: atupal1
PROB: holstein
LANG: C++11
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 26;
int V;
int v[maxn];
int G;
int g[maxn][maxn];

void solve() {
  int min = maxn*maxn;
  int ans = -1;
  for (int i = 1; i < (1<<G); ++ i) {
    int cnt = 0;
    int c[maxn];
    memset(c, 0, sizeof(c));
    for (int j = 0; j < G; ++ j) {
      if ( (i>>j)&1 ) {
        cnt += 1;
        for (int k = 0; k < V; ++ k) {
          c[k] += g[j][k];
        }
      }
    }

    int flag = 1;
    for (int k = 0; k < V; ++ k) {
      if (c[k] < v[k]) {
        flag = 0;
        break;
      }
    }

    if (flag && cnt < min) {
      min = cnt;
      ans = i;
    }

  }

  printf("%d", min);
  for (int j = 0; j < G; ++ j) {
    if ( (ans>>j)&1 ) {
      printf(" %d", j+1);
    }
  }

  printf("\n");

}

int main() {
  char *HOME = getenv("HOME");
  if (strcmp(HOME, "/home/atupal") != 0) {
    freopen("holstein.in", "r", stdin);
    freopen("holstein.out","w", stdout);
  }
  scanf("%d", &V);
  for (int i = 0; i < V; ++ i) {
    scanf("%d", v+i);
  }
  scanf("%d", &G);
  for (int i = 0; i < G; ++ i) {
    for (int j = 0; j < V; ++ j) {
      scanf("%d", g[i]+j);
    }
  }
  solve();

  return 0;
}

