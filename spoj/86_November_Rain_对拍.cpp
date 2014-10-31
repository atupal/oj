#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int mm=88888;
const int mn=2222222;
struct point
{
    int x,y,id,fl;
}g[mm];
double a[mm],b[mm],c[mm];
int head[mm],ver[mn],next[mn];
int sum[mm],cov[mm],q[mm],h[mm],s[mm],d[mm],flag[mm],down[mm];
int i,j,k,l,r,x1,x2,y1,y2,n,m,edge;
bool cmp(point a,point b)
{
    return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
void addedge(int u,int v)
{
    ver[edge]=v,++d[v],next[edge]=head[u],head[u]=edge++;
}
void add(point p)
{
    down[p.id]=p.fl;
    if(!flag[p.id])
    {
        flag[p.id]=1;
        int i=r++;
        while(i>0&&(-a[q[i]]*p.x-c[q[i]])/b[q[i]]>p.y)q[i+1]=q[i],--i;
        q[++i]=p.id;
    }
    else flag[p.id]=2;
}
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    scanf("%d", &n);
    while(scanf("%d",&n)!=-1)
    {
        for(m=0,i=1;i<=n;++i)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            a[i]=y1-y2,b[i]=x2-x1,c[i]=x1*y2-x2*y1;
            s[i]=min(x1,x2);
            h[i]=min(y1,y2);
            j=y1<y2;
            g[m].x=x1,g[m].y=y1,g[m].fl=j,g[m].id=i,m++;
            g[m].x=x2,g[m].y=y2,g[m].fl=!j,g[m].id=i,m++;
            d[i]=cov[i]=flag[i]=sum[i]=0;
            head[i]=-1;
        }
        sort(g,g+m,cmp);
        r=edge=i=0;
        while(i<m)
        {
            x1=g[i].x;
            add(g[i++]);
            while(i<m&&g[i].x==x1)add(g[i++]);
            for(j=1;j<=r;++j)
            {
                if(!cov[q[j]])sum[q[j]]+=x1-s[q[j]];
                s[q[j]]=x1;
            }
           for(j=1;j<r;++j)
                if(down[q[j+1]])addedge(q[j+1],q[j]);
            for(k=0,j=1;j<=r;++j)
                if(flag[q[j]]<2)q[++k]=q[j];
            for(r=k,j=1;j<=r;++j)down[q[j]]=0,cov[q[j]]=1;
            cov[q[r]]=0;
        }
        for(r=0,i=1;i<=n;++i)
            if(!d[i])q[r++]=i;
        for(l=0;l<r;++l)
            for(i=head[q[l]];i>=0;i=next[i])
            {
                sum[ver[i]]+=sum[q[l]];
                if(--d[ver[i]]==0)q[r++]=ver[i];
            }
        for(i=1;i<=n;++i)printf("%d\n",sum[i]);
        printf("\n");
    }
    return 0;
}
