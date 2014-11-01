#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int map[205][205];
int cnt[201];

void init(int i) {
  int ind = 1;
  while (map[i][ind] != i){
    ind ++;
    map[i][ind] = map[map[i][ind-1]][1];
  }
  cnt[i] = ind;
}

int main() {
  int n;
  while (scanf("%d", &n), n){
    int i = n;
    while (i--) {
      scanf("%d", &map[n-i][1]);
    }
    for (int i = 1; i <= n; ++ i) {
      init(i);
      map[i][0] = i;
    }

    int k;
    while ((scanf("%d", &k), k)) {
      char str[n+2];
      for (int x=0; x <= n; ++ x) str[x]=' ';
      int ind=0;
      while (1) {
        char c;
        scanf("%c", &c);
        if (c != '\n') 
          str[ind++] = c;
        else
          break;
      }
      char ret[n+2];
      for (int x=1; x <= n; ++ x) {
        ret[map[x][ k % cnt[x]  ]] = str[x];
      }
      int len = n;
      while (ret[len] == ' ') --len;
      for (int x =1; x <=len; ++ x) 
        printf("%c", ret[x]);
      printf("\n");
    }
    printf("\n");
  }
}
