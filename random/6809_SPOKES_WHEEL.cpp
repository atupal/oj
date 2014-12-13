/*
https://icpcarchive.ecs.baylor.edu/external/68/6809.pdf
 */

#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

const int maxn = 33;

typedef unsigned int int32;

char s1[maxn];
char s2[maxn];
int32 a, b;

int main() {
  int t;
  ios::sync_with_stdio(0);
  cin >> t;
  for (int c = 1; c <= t; ++ c) {
    cin >> s1 >> s2;
    a = b = 0;
    for (char *s = s1; *s; ++ s) {
      a = a * 16 + ( *s >= '0' && *s <= '9' ? *s - '0' : *s - 'A' + 10);
    }
    for (char *s = s2; *s; ++ s) {
      b = b * 16 + ( *s >= '0' && *s <= '9' ? *s - '0' : *s - 'A' + 10);
    }
    int ansl = 32, ansr = 32;
    for (int i = 0; i < 32; ++ i) {
      if ( ((a<<i)|(a>>(32-i)))  == b and ansl == 32) {
        ansl = i;
      }
      if (  ( (a<<(32-i)) | (a>>(32-(32-i))) )  == b and ansr == 32) {
        ansr = i;
      }
    }
    if (ansl < ansr) {
      cout << "Case #" << c << ":" << " " << ansl << " Left" << endl;
    } else if (ansr < ansl) {
      cout << "Case #" << c << ":" << " " << ansr << " Right" << endl;
    } else if (ansl != 32) {
      cout << "Case #" << c << ":" << " " << ansl << " Any" << endl;
    } else {
      cout << "Case #" << c << ":" << " " << "Not possible" << endl;
    }
  }

  return 0;
}
