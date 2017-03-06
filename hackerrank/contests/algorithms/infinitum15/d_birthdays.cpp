#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double p[400];

void init() {
  for (int n = 1; n <= 100; ++ n) {

    int leapcnt = n / 4;

    double ret = 1;

    double tmp = 365;

    for (int i = 0; i < (n-leapcnt); ++ i) {
      ret *= tmp/(double)365.;
      -- tmp;
    }

    tmp += 1;
    for (int i = 0; i < leapcnt; ++ i) {
      ret *= tmp/(double)366.;
      -- tmp;
    }

    p[n] = (double)1.0 - ret;

  }
}

int main() {
  int n;

  init();


  scanf("%d", &n);
  for (int t = 0; t < n; ++ t) {
    double input;
    scanf("%lf", &input);

    if (input == 1) {
      printf("367\n");
      continue;
    }

    for (int i = 1; i <= 366; ++ i) {
      if (p[i] >= input) {
        printf("%d\n", i);
        break;
      }
    }
  }

  return 0;
}
