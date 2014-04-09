#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBU

int m,n;

struct thing {
  int p;
  int l;
  int cnt;
};

inline int Min(int a, int b) {
  return a < b ? a : b;
}

inline int Max(int a, int b) {
  return a > b ? a : b;
}

inline int abs(int a) {
  return a > 0 ? a : -a;
}

thing th[102];
//int dp[102][50][50];
//int ***dp; 
int dp[101];
//int ***pre;
//int seq[102];
//int be[102];
//int en[102];

//int bem[102][102];
//int enm[102][102];
int chea[102][102];
//int stack[102];
int size;

int max_ri = 0;
int min_lo = -1;

/*
void init() {
  for (int i = 1; i <= n; ++ i) {
    if ( not be[i] ) {
      stack[ ++stack[0] ] = i;
      vis[i] = 1;
    }
  }

  cnt = 0;
  while ( stack[0] ) {
    seq[cnt++] = stack[ stack[0] --];
    int ind = seq[cnt-1];
    for ( int i = 1; i <= enm[ind][0]; ++ i ) {
      be[ enm[ind][i] ] --;
    }

    for (int i = 1; i <= n; ++ i) {
      if (not be[i] and not vis[i]) {
        stack[ ++stack[0] ] = i;
        vis[i] = 1;
      }
    }
  }
#ifdef DEBUG
  for (int i = 0; i < cnt; ++ i) 
    printf("%d\t", seq[i]);
  printf("\n");
#endif
}
*/

int get(int x, int l, int r) {
  if (dp[x]!= -1) return dp[x];

  dp[x] = th[x].p;
  for ( int i = 1; i <= n; ++ i ) {
    int jnd = i;
    if ( chea[x][i] and th[jnd].l <= r and th[jnd].l >= l ) {
      dp[x] = Min(dp[x], get(jnd, Max(l, th[jnd].l-m) , Min(r, th[jnd].l+m) ) + chea[x][jnd] );
    }
  }

  return dp[x];
}

void solve() {
  memset(dp, -1, sizeof(dp));
  /*
  int i;
  int j=0;
  for (i = 0; i < n; ++ i) {
    int ind = seq[i];
    if ( not bem[ ind ][0] ) {
      for (int i = min_lo; i <= max_ri; ++ i) {
        for (int j = i; j <= max_ri; ++ j) {
          dp[ind][i][j] = th[ind].p;
        }
      }
    } else {
      if (not j) j = i;
      for (int i = min_lo; i <= max_ri; ++ i) {
        for (int j = i; j <= max_ri; ++ j) {
          dp[ind][i][j] = th[ind].p;
        }
      }
    }
  }

  i=j;
  for (; i < n; ++ i) {
    int ind = seq[i];
    for (int lo = min_lo; lo <= max_ri; ++ lo) {
      for (int ri = lo; ri <= max_ri; ++ ri) {

          int min = th[ind].p;
          for ( int x = 1; x <= bem[ind][0]; ++ x ) {

            int jnd = bem[ind][x];

            if ( th[jnd].l <= ri and th[jnd].l >= lo )
              min = Min(min,   dp[jnd][ Max(lo, th[jnd].l - m) ][ Min(ri, th[jnd].l + m) ] + chea[ind][jnd]  );

          }
          dp[ind][lo][ri]=min;

        }
      }
  }
  */
/*
#ifdef DEBUG
  for (int i = 0; i < n; ++ i) {
    printf("%d:\t", seq[i]);
    printf("%d\t", dp[seq[i]][min_lo][max_ri]);
    printf("\n");
  }
#endif
*/
  //printf("%d\n", dp[1][ Max(0, th[1].l - m) ][ th[1].l + m ]);
  printf("%d\n", get(1, Max(0, th[1].l - m), th[1].l + m  ) );

}

int main() {
  scanf("%d %d", &m, &n);

  for (int i = 1; i <= n; ++ i) {
    int p, l, x;
    scanf("%d %d %d", &p, &l, &x);
    th[i].p = p;
    th[i].l = l;
    max_ri = Max(max_ri, l);
    min_lo = ( l < min_lo or min_lo == -1 ) ? l : min_lo;
    th[i].cnt = x;
    //be[i] = x;
    //bem[i][0] = x;

    for (int j = 0; j < x; ++ j) {
      int t, v;
      scanf("%d %d", &t, &v);
      //th[i].next[j] = t;
      //th[i].chea[j] = v;
      chea[i][t] = v;
      //bem[i][j+1] = t;
      //++ enm[t][0];
      //en[t] ++;
      //enm[t][ enm[t][0] ] = i;
    }
  } 
  //min_lo = Max(0, min_lo - m);
  //max_ri += m;
  min_lo = Max(0, th[1].l - m);
  max_ri = th[1].l + m;
#ifdef DEBUG
  printf("%d:%d\n", min_lo, max_ri);
#endif
  size = (n+2) *  (max_ri + m + 2) * (max_ri + m + 2);

  //dp = (int***)malloc(sizeof(int**) * (n+2));
  //pre = (int***)malloc(sizeof(int**) * (n+2));
  /*
  for (int i = 0; i < n + 2; ++ i) {
    dp[i] = (int**) malloc (sizeof(int*) * (max_ri + m + 2));
    //pre[i] = (int**) malloc (sizeof(int*) * (max_ri + m + 2));
    for (int j = 0; j < max_ri + m + 2; ++ j) {
      dp[i][j] = (int*) malloc (sizeof(int) * (max_ri + m + 2));
      //pre[i][j] = (int*) malloc (sizeof(int) * (max_ri + m + 2));
      memset(dp[i][j], -1 ,sizeof(int) * (max_ri + m + 2));
      //memset(pre[i][j], 0 ,sizeof(int) * (max_ri + m + 2));
    }
  }
  */

  //init();
  solve();
}
