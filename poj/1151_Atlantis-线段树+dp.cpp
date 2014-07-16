/*
http://www.cnblogs.com/ka200812/archive/2011/11/13/2247064.html
 */
#include <cstdio>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct node
{
    int l;
    int r;
    int cover;
    double len;
};

node tree[2000];
double yy[250];
int n,len;

struct Line
{
    double y_down;
    double y_up;
    double x;
    int cover;
};

Line line[250];

int cmp(Line a,Line b)
{
    return a.x<b.x;
}

int find(double x)
{
    int l=0,r=len,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(yy[mid]==x)
            return mid;
        if(yy[mid]<x)
            l=mid+1;
        else
            r=mid-1;
    }
    return l;
}

void build(int i,int l,int r)
{
    tree[i].l=l;
    tree[i].r=r;
    tree[i].cover=0;
    tree[i].len=0;
    if(l+1==r)
        return;
    int mid=(l+r)/2;
    build(2*i,l,mid);
    build(2*i+1,mid,r);
}

void fun(int i)
{
    if(tree[i].cover)
        tree[i].len=yy[tree[i].r]-yy[tree[i].l]; //如果cover大于1，那么整段都可用于与下一线段求并面积
    else if(tree[i].l+1==tree[i].r) //叶子线段
        tree[i].len=0;
    else
        tree[i].len=tree[2*i].len+tree[2*i+1].len; //很简单的dp
}

void updata(int i,int l,int r,int cover)
{
    if(tree[i].l>r || tree[i].r<l)
        return;
    if(tree[i].l>=l && tree[i].r<=r)
    {
        tree[i].cover+=cover;
        fun(i);
        return;
    }
    updata(2*i,l,r,cover);
    updata(2*i+1,l,r,cover);
    fun(i);
}

int main()
{
    double x1,y1,x2,y2;
    int i,m,a,b,cas=1;
    while(scanf("%d",&n)==1 && n)
    {
        m=0;
        for(i=0;i<n;i++)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            yy[m]=y1;
            line[m].cover=1;
            line[m].x=x1;
            line[m].y_down=y1;
            line[m++].y_up=y2;

            yy[m]=y2;
            line[m].cover=-1;
            line[m].x=x2;
            line[m].y_down=y1;
            line[m++].y_up=y2;
        }
        sort(yy,yy+m);
        len=1;
        for(i=1;i<m;i++)
        {
            if(yy[i-1]!=yy[i])
                yy[len++]=yy[i];
        }
        len--;
        build(1,0,len);
        sort(line,line+m,cmp);
        double ans=0;
        printf("Test case #%d\n",cas++);
        for(i=0;i<m-1;i++)
        {
            a=find(line[i].y_down);
            b=find(line[i].y_up);
            updata(1,a,b,line[i].cover);
            ans+=tree[1].len*(line[i+1].x-line[i].x);  //tree[1].len已经保留了整个树与line[i+1]所能求并面积的长度
        }
        printf("Total explored area: %0.2lf\n\n",ans);
    }
    return 0;
}
