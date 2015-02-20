#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int t[100];

int get(int base, int n) {
  int cnt = 0;
  while (n) {
    t[cnt++] = n%base;
    n /= base;
  }
  for (int i = 0; i < cnt/2; ++ i) {
    if (t[i] != t[cnt-1-i]) return 0;
  }
  return 1;
}

int main() {
  int n;
  scanf("%d", &n);
  int ans = 0;
  for (;;) {
    ++ n;
    int cnt = 0;
    for (int i = 2; i <= 20; ++ i) {
      if (get(i, n)) ++ cnt;
      if (cnt >= 3) {
        printf("%d\n", n);
        ++ ans;
        break;
      }
    }
    if (ans == 20) return 0;
  }

  return 0;
}
