/*
ID: atupal1
PROG: test
LANG: C++11
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  char *HOME = getenv("HOME");
  if (strcmp(HOME, "/home/atupal") != 0) {
    freopen(".in", "r", stdin);
    freopen(".out","w", stdout);
  }

  return 0;
}

