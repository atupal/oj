#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define abs(a) ( (a) > 0 ? (a) : (-(a)) )
#define max(a, b) ( (a) > (b) ? (a) : (b) )

int n, k, t;
int T[101], P[101], S[101];
int dp[101][101];
int who[101][101];

int abs(int a) {
  if (a < 0) return -a;
  return a;
}

void swap(int i, int j){
  if (T[i] != T[j]) T[i] ^= T[j] ^= T[i] ^= T[j];
  if (P[i] != P[j]) P[i] ^= P[j] ^= P[i] ^= P[j];
  if (S[i] != S[j]) S[i] ^= S[j] ^= S[i] ^= S[j];
}

void sort(){
  for (int i = 0; i < n; ++ i) {
    int min = i;
    for (int j = i+1; j < n; ++ j) {
      if (T[j] < T[min])
        min = j;
    }
    swap(i, min);
  }
#ifdef DEBUG
  for (int i = 0; i < n; ++ i) printf("%d\t", T[i]); printf("\n");
  for (int i = 0; i < n; ++ i) printf("%d\t", P[i]); printf("\n");
  for (int i = 0; i < n; ++ i) printf("%d\t", S[i]); printf("\n");
  printf("\n");
#endif
}

void solve(){
  memset(dp, 0, sizeof(dp));
  memset(who, 0, sizeof(who));
  for (int i = S[0]; i <= k; ++ i) {
    dp[0][i] = P[0];
    who[0][i] = 0;
  }

  for (int i = 1; i < n; ++ i) {
    for (int j = 1; j <= k; ++ j) {
      int max = dp[i-1][j];
      dp[i][j] = dp[i-1][j];
      who[i][j] = who[i-1][j];
      for (int x = 0; x <= k; ++ x) {
        //if ( abs(last - T[i]) <= abs(  j - x  )) {
        if ( abs( x - S[ who[i-1][x]  ] )  + abs(S[i] - x) + abs( S[i] - j ) <=  abs( T[i] - T[ who[i-1][x] ]) ) {
          int m = P[i] + dp[i-1][x];
          if (m > max) {
            max = m;
            dp[i][j] = m;
            who[i][j] = i;
          }
        }
      }
    }
  }

#ifdef DEBUG
  printf("#\t");
  for (int i = 0; i <= k; ++ i) {
    printf("%d\t", i);
  }
  printf("\n");
  for (int i = 0; i < n; ++ i) {
    printf("%d\t", i);
    for (int j = 0; j <= k; ++ j) {
      printf("%d\t", dp[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  printf("#\t");
  for (int i = 0; i <= k; ++ i) {
    printf("%d\t", i);
  }
  printf("\n");
  for (int i = 0; i < n; ++ i) {
    printf("%d\t", i);
    for (int j = 0; j <= k; ++ j) {
      printf("%d\t", who[i][j]);
    }
    printf("\n");
  }
  printf("\n");
#endif

  int max = dp[n-1][1];
  for (int i = 2; i <= k; ++ i) if (dp[n-1][i] > max) max = dp[n-1][i];
  printf("%d\n", max);
}
 
int main() {
  scanf("%d %d %d", &n, &k, &t);
  for (int i = 0;i < n; ++ i) scanf("%d", T+i);
  for (int i = 0;i < n; ++ i) scanf("%d", P+i);
  for (int i = 0;i < n; ++ i) scanf("%d", S+i);

  sort();
  solve();

  return 0;
}
