#include <stdio.h>

unsigned int cache[1000000];

unsigned int solve(unsigned int n) {
  if (n < 12) {
    return n;
  }
  if (n < 1000000 && cache[n] != 0) {
    return cache[n];
  }

  unsigned int n2 = solve(n / 2);
  unsigned int n3 = solve(n / 3);
  unsigned int n4 = solve(n / 4);
  unsigned int answer = n;
  if (n2 + n3 + n4 > answer) {
    answer = n2 + n3 + n4;
  }

  if (n < 1000000) {
    cache[n] = answer;
  }

  return answer;
}

int main() {
  unsigned int n;
  while (scanf("%u", &n) != EOF) {
    printf("%u\n", solve(n));
  }
}
