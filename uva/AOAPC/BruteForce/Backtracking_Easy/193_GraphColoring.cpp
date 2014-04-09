
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 201;

int n,m;
vector<int> G[maxn];
char col[maxn];
char v[maxn];
char B[maxn];
int ans;
int Max;

void dfs(int cur, int c) {
    if (cur == n + 1) {
        if (c > ans) {
            ans = c;
            memcpy(col, v, sizeof(v));
        }
    }
    if (c + n - cur + 1<= ans) return;
    int flag = 0;
    for (int i = 0; i < (int)G[cur].size(); ++ i) 
        if (v[G[cur][i]]) {
            flag = 1;
            break;
        }
    if (!flag) {
        v[cur] = 1;
        dfs(cur + 1, c + 1);
        v[cur] = 0;
    }
    dfs(cur + 1, c);
}

int main() {
    int tn;
    scanf("%d", &tn);
    while (tn --) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++ i) G[i].clear();
        memset(v, 0, sizeof(v));
        memset(col, 0, sizeof(col));
        memset(B, 0, sizeof(B));
        ans = 0;
        Max = 0;
        for (int i = 0; i < m; ++ i) {
            int u, v;
            scanf("%d %d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        v[1] = 1;
        dfs(1, 0);
        printf("%d\n", ans);
        int first = 0;
        for (int i = 1; i <= n; ++ i) if (col[i]) {
            if(!first) {
                first = 1;
                printf("%d", i);
            }
            else
                printf(" %d", i);
        }
        printf("\n");
    }

    return 0;
}

/*
#include<stdio.h>
const long maxv=102;
long v,e,ans,a[maxv];
bool g[maxv][maxv];
int d[maxv];
bool ok(long node)
{
    for(long i=1;i<=v;i++)
      if(g[node][i]&&d[i]==1)
        return false;
    return true;
}
void dfs(long dep,long now)
{
    if(dep>v)
    {
       if(now>ans)
       {
          ans=now;
          for(long i=1;i<=v;i++) a[i]=d[i];
       }
       return;
    }
    if(now+v-dep+1<=ans) return;
    
    if(ok(dep))
    {
       d[dep]=1;
       dfs(dep+1,now+1);
       d[dep]=0;
    }
    dfs(dep+1,now);
}
int main()
{
    long test;
    bool first;
    scanf("%ld",&test);
    while(test--)
    {
       scanf("%ld%ld",&v,&e);
       for(long i=0;i<=v;i++)
         for(long j=0;j<=v;j++)
           g[i][j]=false;
       for(long i=0;i<=v;i++) d[i]=0;
       ans=0;
       //  Clear
       for(long i=1;i<=e;i++)
       {
          long a,b;
          scanf("%ld%ld",&a,&b);
          g[a][b]=g[b][a]=true;
       }
       dfs(1,0);
       printf("%ld\n",ans);
       first=true;
       for(long i=1;i<=v;i++)
         if(a[i])
         {
            if(first) first=false;
            else putchar(' ');
            printf("%ld",i);
         }
       putchar('\n');
    }
return 0;
}
*/
