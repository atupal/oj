#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <utility>

using namespace std;

#define is_inner(x,y) (x >= 0 and x < 8 and y >= 0 and y < 8 and not vis[x][y])

const int maxn = 65;

struct point {
  int x;
  int y;
};

struct point king;
struct point knights[maxn];
int kn;
int momo[8][8][8][8];
int pre[8][8][8][8];
int vis[8][8];
int map[8][8];
int w[8][8];

int Min(int, int);
int Max(int, int);
int abs(int);

void input(){
  char a;
  char b;
  a = getchar();
  b = getchar();
  king.x = a - 'A';
  king.y = b - '1';
  kn = 0;
  memset(map, 0, sizeof(map));
  while (1) {
    a = getchar();
    if (a == '\n' or a == EOF) {
      break;
    }
    b = getchar();
    knights[kn].x = a - 'A';
    knights[kn].y = b - '1';
    map[knights[kn].x][knights[kn].y] = 1;
    ++ kn;
  }

  memset(momo, -1, sizeof(momo));
  memset(pre, -1, sizeof(pre));
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < 8; ++ i) {
    for (int j = 0; j < 8; ++ j) {
      w[i][j] = Max(abs(i - king.x), abs(j - king.y));
    }
  }
}

struct point direct[] = {
  {-2, -1}, {-2, 1},
  {-1, -2}, {-1, 2},
  {1, 2}, {1, -2},
  {2, 1}, {2, -1}
};

void bfs(int x, int y) {
  memset(vis, 0, sizeof(vis));
  int step = 1;
  queue< pair<int, int> > q;
  q.push(make_pair(x, y));
  int cnt = 1;
  momo[x][y][x][y] = 0;
  while (not q.empty()) {
    int new_cnt = 0;
    while (cnt--) {
      pair<int, int> p = q.front(); q.pop();
      int xx = p.first, yy = p.second;
      vis[xx][yy] = 1;
      for (int i = 0; i < 8; ++ i) {
        int xxx, yyy;
        xxx = xx + direct[i].x;
        yyy = yy + direct[i].y;
        if (is_inner(xxx, yyy)) {
          q.push(make_pair(xxx, yyy));
          ++ new_cnt;
          momo[x][y][xxx][yyy] = step;
          pre[x][y][xxx][yyy] = xx * 100 + yy;
        }
      }
    }
    cnt = new_cnt;
    ++ step;
  }
}

void bfs_2(int sx, int sy, int dx, int dy) {
}

inline
int abs(int x) {
  return x > 0 ? x : -x;
}
inline 
int Max(int a, int b) {
  a = abs(a);
  b = abs(b);
  return a > b ? a : b;
}
inline
int Min(int a, int b) {
  a = abs(a);
  b = abs(b);
  return a < b ? a : b; 
}

void solve() {
  memset(w, -1, sizeof(w));

  for (int i = 0; i < kn; ++ i) {
    bfs(knights[i].x, knights[i].y);
  }

  for (int x = 0; x < 8; ++ x) {
    for (int y = 0; y < 8; ++ y) {
      int min = Max(abs(x-king.x), abs(y-king.y));
      for (int i = 0; i < kn; ++ i) {
        if (momo[knights[i].x][knights[i].y][x][y] == -1) {
          break;
        }
        int p;
        p = pre[knights[i].x][knights[i].y][x][y];
        if (Max(abs(knights[i].x - king.x), abs(knights[i].y - king.y)) < min) {
          min = Max(abs(knights[i].x - king.x), abs(knights[i].y - king.y));
        }
        while (p != -1) {
          printf("%d ", p);
          int xx, yy;
          xx = p / 100;
          yy = p % 100;
          int tmp;
          tmp = Max(abs(xx-king.x), abs(yy-king.y));
          if (tmp < min) {
            min = tmp;
          }
          p = pre[knights[i].x][knights[i].y][xx][yy];
        }
        printf("\n");
      }
      w[x][y] = min;
    }
  }

  printf("\n##########################################\n");

  for (int x = 0; x < 8; ++ x) {
    for (int y = 0; y < 8; ++ y) {
      printf("%d %d: ", x, y);
      int tmp = 0;
      for (int i = 0; i < kn; ++ i) {
        tmp += momo[knights[i].x][knights[i].y][x][y];
        printf("%d\t", momo[knights[i].x][knights[i].y][x][y]);
      }
      printf(" = %d\n", tmp);
    }
  }
  //printf("%d %d: %d\n",knights[1].x, knights[1].y, momo[0][7][3][5]);


  int ans = maxn * maxn;
  int ans_x, ans_y;
  for (int x = 0; x < 8; ++ x) {
    for (int y = 0; y < 8; ++ y) {
      int tmp;
      tmp = 0;
      for (int i = 0; i < kn; ++ i) {
        if (momo[knights[i].x][knights[i].y][x][y] == -1) {
          tmp += maxn * maxn;
          break;
        }
        tmp += momo[knights[i].x][knights[i].y][x][y];
        //printf("%d ", momo[knights[i].x][knights[i].y][x][y]);
      }
      //printf("\n");
      tmp += w[x][y];
      if (tmp < ans) {
        ans = tmp;
        ans_x = x;
        ans_y = y;
      }
    }
  }

  printf("\n");
  for (int i = 0; i < 8; ++ i) {
    for (int j = 0; j < 8; ++ j) {
      if (king.x == i and king.y == j) {
        printf("# ");
      } else if (map[i][j]){
        printf("0 ");
      } else if (i == ans_x and j == ans_y){
        printf("x ");
      } else {
        printf("* ");
      }
    }
    printf("\n");
  }

  for (int i = 0; i < kn; ++ i) {
    printf("%d %d\n", knights[i].x, knights[i].y);
  }
  for (int i = 0; i < kn; ++ i) {
    printf("%d + ", momo[knights[i].x][knights[i].y][ans_x][ans_y]);
  }
  printf("%d = %d\n", w[ans_x][ans_y], ans);

}

int main () {
  input();
  solve();

  return 0;
}
