
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

const int maxn = 101;

int dist;
char g[maxn][maxn];
char v[maxn];
char V[maxn];
int B[maxn];
int tot;
int n;
int cnt[maxn];
int dc;

int cmp(const void *a, const void *b) {
    return *((int*)a) - *((int*)b);
}

void dfs_cnt(int node) {
    for (int i = 1; i <= n; ++ i) if (!v[i] && g[node][i]) {
        cnt[dc++] = i;
        v[i] = 1;
        dfs_cnt(i);
    }
}

void dfs(int cur, int node) {
    B[cur] = node;
    if (node == dist) {
        for (int i = 0; i < cur; ++ i) printf("%d ", B[i]);
        printf("%d\n", dist);
        ++ tot;
    }
    else for (int i = 0; i < dc; ++ i) if (!v[cnt[i]]) if (g[node][cnt[i]]) {
        v[cnt[i]] = 1;
        dfs(cur + 1, cnt[i]);
        v[cnt[i]] = 0;
    }
}

int main() {
    int ct = 0;
    while (scanf("%d", &dist) != EOF) {
        memset(v, 0, sizeof(v));
        memset(g, 0, sizeof(g));
        dc = 0;
        n = 0;
        while (1) {
            int u, v;
            scanf("%d %d", &u, &v);
            if (u + v == 0) break;
            g[u][v] = g[v][u] = 1;
            n = u > n ? u : n;
            n = v > n ? v : n;
        }
        dfs_cnt(dist);
        qsort(cnt, dc, sizeof(int), cmp);
        memset(v, 0, sizeof(v));
        v[1] = 1;
        tot = 0;
        printf("CASE %d:\n", ++ct);
        dfs(0, 1);
        printf("There are %d routes from the firestation to streetcorner %d.\n", tot, dist);
    }

    return 0;
}
/*
#include <stdio.h>
#include <string.h>
#define MAXN 101
int N,fires,g[MAXN][MAXN]={0};
int nums,a[MAXN],la=0,cnt[MAXN]={0},lc;
bool vis[MAXN]={false};
void Init()
{
     int u,v;
     nums=lc=0;
     la=N=0;
     memset(vis,false,sizeof(vis));
     memset(g,0,sizeof(g));
     while(scanf("%d %d",&u,&v)==2)
     {
        if(!u && !v) break;
        if(N<u) N=u;
        if(N<v) N=v;
        g[u][v]=1;
        g[v][u]=1;
     }
}
void dfs_cnt(int v)
{
     cnt[lc++]=v;
     for(int i=1;i<=N;i++)
        if(g[v][i] && !vis[i])
        {
           vis[i]=true;
           dfs_cnt(i);
        }
}
void Qsort(int *a,int x,int y)
{
     if(x>=y) return;
     int p=x,q=y,F=a[x];
     while(p<q)
     {
        while(p<q && a[q]>F )
           q--;
        if(p<q) a[p++]=a[q];
        while(p<q && a[p]<F )
           p++;
        if(p<q) a[q--]=a[p];
     }
     a[p]=F;
     Qsort(a,x,p-1);
     Qsort(a,p+1,y);
}
void dfs(int v)
{
     if(v==fires)
     {
        nums++;
        printf("%d",a[0]);
        for(int i=1;i<la;i++)
           printf(" %d",a[i]);
        printf("\n");
        return;
     }else
     for(int i=0;i<lc;i++)
     {
        int u=cnt[i];
        if(g[v][u] && !vis[u])
        {
           vis[u]=true;
           a[la++]=u;
           dfs(u);
           la--;
           vis[u]=false;
        }
     }
     return;
}
int main()
{
    int cas=0;
    while(scanf("%d",&fires)==1)
    {
       Init();
       vis[fires]=true;
       dfs_cnt(fires);
       //Qsort(cnt,0,lc-1);
       printf("CASE %d:\n",++cas);
       memset(vis,false,sizeof(vis));
       vis[1]=true;
       a[la++]=1;
       dfs(1);
       printf("There are %d routes from the firestation to streetcorner %d.\n",nums,fires);
    }
    return 0;
}
*/
