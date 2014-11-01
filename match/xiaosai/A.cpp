#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int T,n;

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int sed = (n) / 2;
    printf("%d\n", 1 + sed + n*n);
  }
}
