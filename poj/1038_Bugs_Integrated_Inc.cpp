#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int D, N, M;
char black[151][11];
int dp[2][59050];
int p[11];
int q[11];
int r[11];

inline int max(int a, int b) {
  return a > b ? a : b;
}

int compress(int *a) {
  int ret = 0;
  for (int i = 0; i < M; ++ i) {
    ret += a[i] * r[i];
  }
  return ret;
}

void uncompress(int ret, int *a) {
  for (int i = 0; i < M; ++ i) {
    a[i] = ret % 3;
    ret /= 3;
  }
}

void dfs(int i, int x, int num) {
  if (x > M) return;
  int cur = (i+1) & 1, nxt = i&1, k = compress(q);

  dp[nxt][k] = max( dp[nxt][k], dp[cur][compress(p)] );

  if (x < M-1 and  p[x]==0 and p[x+1] == 0 and q[x] == 0 and q[x+1] == 0  ) {
    q[x] = q[x+1] = 2;
    int kk = compress(q);
    dp[nxt][kk] = max(dp[nxt][kk], num+1);
    dfs(i, x+2, num+1);
    q[x] = q[x+1] = 0;
  }

  if ( x < M-2 and q[x]==0 and q[x+1]==0 and q[x+2]==0) {
    q[x] = q[x+1] = q[x+2] = 2;
    int kk = compress(q);
    dp[nxt][kk] = max( dp[nxt][kk], num + 1 );
    dfs(i, x+3, num+1);
    q[x] = q[x+1] = q[x+2] = 0;
  }

  dfs(i, x+1, num);

}

void solve(){
  for (int i = 0; i < M; ++ i) {
    p[i] = black[0][i] + 1;
  }
  dp[0][ compress(p) ] = 0;

  int mask = r[M];
  for (int i = 1; i < N; ++ i) {
    int cur = (i+1) & 1;
    int nxt = i & 1;
    memset(dp[nxt], -1, sizeof(dp[nxt]));

    for (int j = 0; j < mask; ++ j) {
      if (dp[cur][j] == -1) continue;
      uncompress(j, p);

      for (int x = 0; x < M; ++ x) {
        if (black[i][x]) q[x] = 2;
        else {
          q[x] = max( 0, p[x] - 1);
        }
      }

      dfs(i, 0, dp[cur][j]);
    }

  }

  int ans = 0;
  for (int i = 0; i < mask; ++ i) {
    ans = max( ans, max( dp[0][i], dp[1][i] ) );
  }
  printf("%d\n", ans);

}

int main() {
  scanf("%d", &D);

  r[0] = 1;
  for (int i = 1; i < 11; ++ i) {
    r[i] = r[i-1] * 3;
  }

  while (D--) {
    int k;
    scanf("%d %d %d", &N, &M, &k);

    memset(black, 0, sizeof(black));
    memset(dp, -1, sizeof(dp));
    memset(p, 0, sizeof(p));
    memset(q, 0, sizeof(q));

    while (k--) {
      int x,y;
      scanf("%d %d", &x, &y);
      black[x-1][y-1] = 1;
    }
    solve();
  }

  return 0;
}

/*
 * 参考代码
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

const int N = 60000;
int vis[155][11];
int dp[2][60000], A[11], P[11], Q[11];
int n, m, K, mask;

inline int MAX(int a,int b)
{
    return a>b?a:b;
}
int GetState( int f[] )
{
    int res = 0;
    for(int i = 1; i <= m; i++)
        res += (f[i]*A[i-1]);
    return res;
}
void GetBack( int x, int f[] )
{
    for(int i = 1; i <= m; i++)
    {
        f[i] = x%3;    x /= 3;
    }
}

void dfs( int i, int x, int num) // 第i行，x列， 数量为num
{
    if( x > m ) return;    
    int cur = (i+1)&1, nxt = i&1, k = GetState(Q) ;    
        
    // 当前层可不放任意芯片    
    dp[nxt][k] = MAX( dp[nxt][k], dp[cur][ GetState(P) ] );
    
    //情况（1） 当方格 (i+1,x) 不放置芯片时，那么考虑方格(i+1,x), 且 x < m 

    //情况（2） 如果 P[x],P[x+1] = 0, 且区域 (i-1,i+1), (x,x+1)均无黑点 且 i >= 2 && x < m
    //则 竖立放置芯片 3*2， 左下角坐标为 （i+1,x）
    if( (x<=(m-1)) && ( (P[x]==0) && (P[x+1]==0) ) && ( (Q[x]==0)&&(Q[x+1]==0))  )
    {
        Q[x] = Q[x+1] = 2;    
        int kk = GetState(Q);
        dp[nxt][kk] = MAX( dp[nxt][kk], num+1 );
        dfs( i, x+2, num+1 );    
        Q[x] = Q[x+1] = 0;    
    }

    //情况（3） 如果 P[x],P[x+1],P[x+2] <= 1, 且区域 (i,i+1),(x,x+2) 均无黑点 且 i >= 1 && x < m-1
    //则 横着放置芯片 2*3, 左下角坐标为 (i+1,x)
    if( (x<=(m-2)) && ( (!Q[x])&&(!Q[x+1])&&(!Q[x+2]) )  )
    {        
        Q[x]=Q[x+1]=Q[x+2] = 2;    
        int kk = GetState(Q);
        dp[nxt][kk] = MAX( dp[nxt][kk], num+1 );
        dfs( i, x+3, num+1);
        Q[x]=Q[x+1]=Q[x+2] = 0;    
    }
    
    dfs( i, x+1, num );  
}
void solve()
{
    // 初始化为 -1，标明该 状态不可用
    memset( dp, 0xff, sizeof(dp) );
    memset( P, 0, sizeof(P));
    memset( Q, 0, sizeof(Q));
    for(int i = 1; i <= m; i++)
        P[i] = vis[1][i]+1;  //损坏点看作 已占用。。
    // 初始化第一层状态， 抽象把第0层看作皆被占用，合法状态仅一种，且方案数为0
    dp[1][ GetState(P) ] = 0;     

    mask = A[m];
    // 0: i,i-1层位置皆为空
    // 1：i层为空，i-1层已占用
    // 2：i层已占用
    for(int i = 2; i <= n; i++)
    {
        int cur = (i+1)&1, nxt= i&1;    
        // 已知 dp(i,j) 状态j表示 i,i-1层 放置编号
        // 初始化下一层nxt，初始时皆为不可用
        memset( dp[nxt], 0xff, sizeof(dp[nxt]) );

        for(int j = 0; j < mask; j++)
        {
            if( dp[cur][j] == -1 ) continue; //若当前状态不合法    
            //I层 放置编号J 解压成 放置序列 P[]        
            GetBack( j, P );
            
            //获取 I+1层 放置序列 Q[], 且把第I+1层 损坏位置看做已占用，添加到状态中
            for(int x = 1; x <= m; x++)
            {
                if( vis[i][x] ) Q[x] = 2;
                else
                { //去除掉 I-1层 的信息，存储I，I+1放置信息
                    Q[x] = P[x]-1;
                    if( Q[x] < 0 ) Q[x] = 0; 
                }
            }
            // 获取第I+1行 放置状态以及数量    
            dfs( i, 1,  dp[cur][j] ); //行i,列j，目前芯片数量 dp[cur][j]
        }
    }

    int ans = 0;
    for(int i = 0; i < mask; i++)
        ans = MAX( ans, MAX(dp[0][i],dp[1][i]) );
    printf("%d\n", ans );
}
int main()
{
    freopen("test.in","r",stdin);
    freopen("mytest.out", "w", stdout);
    A[0] = 1;
    for(int i = 1; i <= 10; i++ ) A[i] = 3*A[i-1];
    int T;
    scanf("%d", &T);
    while( T-- )
    {
        scanf("%d%d%d", &n,&m,&K);    
        int x, y; 
        memset( vis, 0, sizeof(vis));
        
        for(int i = 0; i < K; i++)
        {
            scanf("%d%d", &x,&y);
            vis[x][y] = 1;
        }
    
        solve();
    }
    return 0;
}
*/
