#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char map[20][20];
char vis[20][20];

int col_cnt[200];
  
int ind = 0;
int cc = 0;

int col_empty(int c) {
  for (int i = 1; i<= 10; ++i) {
    if (map[i][c]) return 0;
  }
  return 1;
}

void ref(char col) {
  for (int i = 1; i <= 10; ++ i) {
    for (int j = 1; j<= 15; ++ j) {
      if (vis[i][j] == col) {
        cc += 1;
        map[i][j] = 0;
      }
    }
  }

  for (int i = 1; i <= 15; ++ i) {
    for(;;) {
      int flag = 0;
      for (int j = 10; j; j--) {
        if (not map[j][i] and map[j-1][i]) {
          flag = 1;
          map[j][i] = map[j-1][i];
          map[j-1][i]=0;
        }
      }
      if (not flag) break;
    }
  }

  for (;;) {
    int flag = 0;
    for (int i = 1; i < 15; ++ i) {
      if (col_empty(i) and not col_empty(i+1)) {
        flag = 1;
        for (int x = 1; x <= 10; ++ x) {
          map[x][i] = map[x][i+1];
          map[x][i+1] = 0;
        }
      }
    }
    if (not flag) break;
  }
}

void dfs(int r, int c, int col) {
  if (not vis[r][c]) {
    vis[r][c] = col;
    col_cnt[col] += 1;
    int xx[] = {-1, 1, 0, 0};
    int yy[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++ i) {
      int x = r + xx[i];
      int y = c + yy[i];
      if (x > 0 and x <= 10 and y > 0 and y <= 15) {
        if (map[x][y] == map[r][c]) {
          dfs(x,y , col);
        }
      }
    }
  } 
}

int remove() {
  memset(vis, 0, sizeof(vis));
  memset(col_cnt, 0, sizeof(col_cnt));

  int col = 0;
  int max_col = -1;
  for (int i = 1; i <= 10; ++ i) {
    for (int j = 1; j <= 15; ++ j) {
      if (not vis[i][j] and map[i][j]) {
        dfs(i, j , ++ col);
        if (col_cnt[col] > max_col) {
          max_col = col_cnt[col];
        }
      }
    }
  }

  if (max_col >= 2) {

    for (int j = 1; j <= 15; ++ j) {
      for (int i = 10; i; --i) {
        if (col_cnt[  (int)vis[i][j] ] == max_col) {
          printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n", 
              ind, 11 - i, j, max_col, map[i][j], (max_col-2) * (max_col-2));
          ref( vis[i][j]  );
          return (max_col - 2) * (max_col - 2);
        }
      }
    }
  }

  return -1;
}

#include <iostream>
using namespace std;
int DEBUG=0;
int main() {
  int n;
  //scanf("%d\n", &n);
  cin >> n;
  for (int i = 1; i <= n; ++ i) {
    ind = 0;
    if(i > 1)  printf("\n");  // 唔
    printf("Game %d:\n\n", i);
    memset(map, 0, sizeof(map));
    int rcnt = 10;
    while (rcnt--) {
      //scanf("%s", map[10-rcnt]);
      cin >> map[10-rcnt];
    }

    for (int i = 15; i ; -- i) {
      for (int j = 1; j <= 10; ++ j) {
        map[j][i] = map[j][i-1];
      }
    }

    int score = 0;
    cc = 0;
    for (;;) {

      ind ++;
      int ret = remove();
      if (-1== ret) break;
      score += ret;
    }
    if (cc == 15 * 10) 
      score += 1000;
    printf("Final score: %d, with %d balls remaining.\n", score, 15 * 10 - cc);

  }
  return 0;
}
