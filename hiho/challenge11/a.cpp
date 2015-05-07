#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 505;
int n;
double fib[maxn];

double get(int n) {
  if (fib[n] != 0) return fib[n];
  double &ret = fib[n];
  ret = 0;

  double cnt = 0;
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < n; ++ j) {
      cnt += 1;
      ret += get(i)+get(j);
    }
  }

  ret /= cnt;

  return ret;
}

int main() {
  for (int i = 0; i < maxn; ++ i) {
    fib[i] = 0;
  }
  fib[0] = 1;
  while (scanf("%d", &n) != EOF) {
    //printf("%.6lf", get(n));
    printf("%.6lf", (double)n+1);
  }

  return 0;
}

