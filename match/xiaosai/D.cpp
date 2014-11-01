
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 10001

int T,n;
int da[maxn];
int a[32];
int b[32];


void get() {
}

void solve(){
  memset(a, 0, sizeof(a));
  int cnt = 0;
  for (int i = 0; i < 31; ++ i) {
    int base = 1 << i;
    for (int x = 0; x < n; ++ x) {
      if ( base & da[x] ) {
        a[i]++;
        cnt ++;
      }
    }
  }

  printf(cnt % 2 ? "yes\n" : "no\n");
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
      scanf("%d", &da[i]);
    }
    solve();
  }
}
