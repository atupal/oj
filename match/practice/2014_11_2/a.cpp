#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 110;
int M[maxn][maxn];
int n, k;
int v, x, y;


void init() {
  scanf("%d", &n);
  scanf("%d", &k);
  memset(M, 0, sizeof(M));
  for (int i  = 0;  i< k; ++ i) {
    scanf("%d %d %d", &v, &x, &y);
    M[x][y] = v;
  }
}

long long ans = 0;
void move(char d, int v, int xx, int yy) {
  if (d == 'L') {
    for (int i = 1; i <= n; ++ i) {
      int ind = 0;
      int p = 1;
      int flag = 1;
      int pre;
      while (p <= n) {
        if (flag) {
          while (p <= n && M[i][p] == 0)
            p += 1;
          pre = M[i][p];
          p += 1;
          flag = 0;
        }

        while (p <= n && M[i][p] == 0) 
          p += 1;
          
        if (pre == M[i][p] && pre) {
          ind += 1;
          M[i][ind] = pre<<1;
          ans += pre<<1;
          flag = 1;
        }
        else if( pre) {
          ind += 1;
          M[i][ind] = pre;
          pre = M[i][p];
        }

        p += 1;
      }

      if (!flag && pre) {
        ind += 1;
        M[i][ind] = pre;
      }
      for (int x = ind+1; x <= n; ++ x)
        M[i][x] = 0;
    }
  } else if (d == 'R') {
    for (int i = 1; i <= n; ++ i) {
      int ind = n+1;
      int p = n;
      int flag = 1;
      int pre;
      while (p) {
        if (flag) {
          while (p&& M[i][p] == 0)
            p -= 1;
          pre = M[i][p];
          if (p)p -= 1;
          flag = 0;
        }

        while (p&& M[i][p] == 0) 
          p -= 1;
          
        if (pre == M[i][p] && pre) {
          ind -= 1;
          M[i][ind] = pre<<1;
          ans += pre<<1;
          flag = 1;
        }
        else if( pre) {
          ind -= 1;
          M[i][ind] = pre;
          pre = M[i][p];
        }

        if (p) p -= 1;
      }

      if (!flag && pre) {
        ind -= 1;
        M[i][ind] = pre;
      }
      for (int x = 1; x < ind; ++ x)
        M[i][x] = 0;
    }
  } else  if (d == 'U') {
    for (int i = 1; i <= n; ++ i) {
      int ind = 0;
      int p = 1;
      int flag = 1;
      int pre;
      while (p <= n) {
        if (flag) {
          while (p <= n && M[p][i] == 0)
            p += 1;
          pre = M[p][i];
          p += 1;
          flag = 0;
        }

        while (p <= n && M[p][i] == 0) 
          p += 1;
          
        if (pre == M[p][i] && pre) {
          ind += 1;
          M[ind][i] = pre<<1;
          ans += pre<<1;
          flag = 1;
        }
        else if( pre) {
          ind += 1;
          M[ind][i] = pre;
          pre = M[p][i];
        }

        p += 1;
      }

      if (!flag && pre) {
        ind += 1;
        M[ind][i] = pre;
      }
      for (int x = ind+1; x <= n; ++ x)
        M[x][i] = 0;
    }
  } else if (d == 'D') {
    for (int i = 1; i <= n; ++ i) {
      int ind = n+1;
      int p = n;
      int flag = 1;
      int pre;
      while (p) {
        if (flag) {
          while (p&& M[p][i] == 0)
            p -= 1;
          pre = M[p][i];
          if (p)p -= 1;
          flag = 0;
        }

        while (p&& M[p][i] == 0) 
          p -= 1;
          
        if (pre == M[p][i] && pre) {
          ind -= 1;
          M[ind][i] = pre<<1;
          ans += pre<<1;
          flag = 1;
        }
        else if( pre) {
          ind -= 1;
          M[ind][i] = pre;
          pre = M[p][i];
        }

        if (p) p -= 1;
      }

      if (!flag && pre) {
        ind -= 1;
        M[ind][i] = pre;
      }
      for (int x = 1; x < ind; ++ x)
        M[x][i] = 0;
    }
  }
  M[xx][yy] = v;
}


//def out():
//  print
//  for i in xrange(1, n+1):
//    for j in xrange(1, n+1):
//      print M[i][j],
//    print
//  print

int main() {
  init();
  int l;
  scanf("%d", &l);
  char d[2];
  int v, x, y;
  for (int i = 0; i < l; ++ i) {
    scanf("%s %d %d %d", d, &v, &x, &y);
    move(d[0], v, x, y);
  }
  
  printf("%I64d\n", ans);
  return 0;
}
