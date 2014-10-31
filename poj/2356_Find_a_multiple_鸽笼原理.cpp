/*
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn = 15000;
int n;
int s[maxn];
int pos[maxn];

void solve () {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d", s+i);
  }
  memset(pos, -1, sizeof(pos));
  int sum = 0;;
  for (int i = 0; i < n; ++ i) {
    sum += s[i] % n;
    sum %= n;
    if (sum == 0) {
      printf("%d\n", i+1);
      for (int x = 0; x <= i; ++ x) {
        printf("%d\n", s[x]);
      }
      return;
    } else {
      if (pos[sum] == -1) pos[sum] = i;
      else {
        printf("%d\n", i-pos[sum]);
        for (int x = pos[sum]+1; x <= i; ++ x) {
          printf("%d\n", s[x]);
        }
        return;
      }
    }
  }
}

int main() {
  solve();

  return 0;
}
