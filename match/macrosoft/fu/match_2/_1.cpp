#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <queue>
using namespace std;

const int N = 210;
const int INF = 10000000;
int n,m;
int map[N][N],path[N],flow[N],start,end;

queue<int> q;
int flag;

int bfs(){
    int i,t;
    while(!q.empty()) q.pop();   //清空队列

    memset(path,-1,sizeof(path));  //保存父亲的数组，初始化为-1
    path[start]=0,flow[start]=INF;   //flow[] 保存当前的最小容量

    q.push(start);
    while(!q.empty()){
        t=q.front();
        q.pop();
        if(t==end) break;   //找到一条增广路
        for(i=1;i<=m;i++){
            if(i!=start && path[i]==-1 && map[t][i]){
                flow[i]=flow[t]<map[t][i]?flow[t]:map[t][i];
                q.push(i);
                path[i]=t;
            }
        }
    }
    if(path[end]==-1) return -1;   //如果汇点的父亲等于-1，说明不能到达最后。
    return flow[m];                   //一次遍历之后的流量增量，min
}
int ff(){
    int max_flow=0,step,now,pre;
    while((step=bfs())!=-1){          //找不到增路径时退出
        max_flow+=step;
        now=end;
        while(now!=start){
            pre=path[now];
            map[pre][now]-=step;      //更新正向边的实际容量
            map[now][pre]+=step;      //添加反向边
            now=pre;
        }
    }
    return max_flow;
}

int main(){
    int i,u,v,cost;
    int T;
    scanf("%d", &T);
    for (int c = 1; c <= T; ++ c) {
        scanf("%d %d",&m,&n);
        memset(map,0,sizeof(map));
        printf("Case #%d:\n",c);
        start=1,end=m;
        for(i=0;i<n;i++){
            scanf("%d %d %d",&u,&v,&cost);
            map[u][v]+=cost;           //not just only one input
            map[v][u]+=cost;           //not just only one input
            int tmp = ff();
            if(tmp)printf("%d %d\n", i + 1,tmp);
        }
    }
    return 0;
}


/*



const int maxn = 201;
int n,m;
int g[maxn][maxn];
int c[maxn][maxn];




int main() {
    int T;
    scanf("%d", &T);
    for (int c = 1; c <= T; ++ c) {
        memset(g, 0, sizeof(g));
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; ++ i) {
            int x, y;
            scanf("%d %d", &x, &y);
            scanf("%d", &c[x][y]);
        }
    }

    return 0;
}
*/
