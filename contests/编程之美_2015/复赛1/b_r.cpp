
#include<bits/stdc++.h>

#define maxn 200005

using namespace std;

int a[maxn];
int p[maxn];
int L[maxn];
int R[maxn];
int G[1005][1005];

int i,n,q,x,y,k,Kuai,Fen,N;

int md() {
    int u=1000000010;
    scanf("%d%d%d",&x,&y,&k);
    int X=p[x];
    int Y=p[y];
    if (X==Y) {
        for (int i=x;i<=y;i++)
        u=min(u,abs(a[i]-k));
        printf("%d\n",u);
    }
    else {
      while(x<=n && p[x]==X) {
      if (u>abs(a[x]-k)) u=min(u,abs(a[x]-k));
        x++;
    }
      while(y>0 && p[y]==Y)
    {
      if (u>abs(a[y]-k)) u=min(u,abs(a[y]-k));
        y--;
    }
    for (int i=X+1;i<=Y-1;i++) {
        int len=Kuai;
        int v=lower_bound(G[i]+1,G[i]+Kuai+1,k)-G[i];
        if (v!=len+1)
          if (u>abs(G[i][v]-k))  u=abs(G[i][v]-k);
        if (v-1!=0)
          if (u>abs(G[i][v-1]-k)) u=abs(G[i][v-1]-k);
        if (v+1!=len+1)
          if (u>abs(G[i][v+1]-k))  u=abs(G[i][v+1]-k);
    }

    printf("%d\n",u);
    }

    return 0;
}

int main() {
    int T;
    scanf("%d",&T);

    for (int cas = 1; cas <= T; ++ cas) {
        printf("Case #%d:\n",cas);
        N=1;Fen=0;
        scanf("%d%d",&n,&q);
        Kuai=sqrt(n+1);
        for (i=1;i<=n;i++)
           scanf("%d",&a[i]);
        for (i=1;i<=n;i++)
        {
            G[N][++Fen]=a[i];
            p[i]=N;
            if (Fen==Kuai)
              Fen=0,N++;
        }
        for (int i=1;i<=N;i++)
            sort(G[i]+1,G[i]+Kuai+1);
        while(q--) {
            md();
        }
    }
    return 0;
}
