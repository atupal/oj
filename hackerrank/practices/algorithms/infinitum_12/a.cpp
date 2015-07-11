#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;
int a[100];

void solve() {
  scanf("%d", &n);
  for (int i = 0; i <= n; ++ i) {
    scanf("%d", a+i);
  }

  printf("%d %d\n", -a[n-1]/a[n], ( (n&1)?-a[0]:a[0] )/a[n]);

}

int main() {
  solve();

  return 0;
}
