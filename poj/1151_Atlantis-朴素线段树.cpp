/*
http://www.cnblogs.com/ka200812/archive/2011/11/13/2247064.html
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=110;

struct LINE
{
    double  x, y_down, y_up;
    int  flag;
    bool operator<(const LINE &a)const
    {
        return  x<a.x;
    }
}line[2*maxn];

struct TREE
{
    double  y_down, y_up;
    double  x;
    int     cover; //用以表示加进线段树中的线段次数
    bool    flag; //此标记用来表示是否有超元线段；为了处理方便加上去的
}tree[1000*maxn];

int     n;
double  x1, y1, x2, y2;
int     index=0;
double  y[2*maxn];

void build(int i, int l, int r)
{
       tree[i].x = -1; //-1表示该区间已经没有线段
       tree[i].cover = 0; //表示该区间上有多少条线段；左边线段加进去则++，右边线段加进去则--
       tree[i].y_down = y[l];
       tree[i].y_up = y[r];
       tree[i].flag = false;
       if(l+1==r)
       {
           tree[i].flag = true; //flag==true表示达到了叶子节点
           return;
       }
       int mid=(l+r)>>1;
       build(2*i, l, mid);
       build(2*i+1, mid, r);
}

double insert(int i, double x, double l, double r, int flag) //flag表示为左边还是右边
{
    if (r<=tree[i].y_down || l>=tree[i].y_up) 
        return 0;
    if (tree[i].flag) 
    {
        if (tree[i].cover > 0) //递归到了叶子节点
        {
             double temp_x = tree[i].x;
             double ans=(x-temp_x)*(tree[i].y_up - tree[i].y_down);
             tree[i].x = x;   //定位上一次的x
             tree[i].cover += flag;
             return ans;
        }
        else 
        {
            tree[i].cover += flag;
            tree[i].x = x;
            return 0;
        }
    }
    double ans1, ans2;
    ans1 = insert(2*i, x, l, r, flag);
    ans2 = insert(2*i+1, x, l, r, flag);
    return ans1+ans2;
}

int main( )
{
   // freopen("d:\\in.txt","r",stdin);
    int  count=0;
    while (scanf("%d", &n)!=EOF&&n)
    {
        index = 1;
        for (int i=1; i<=n; i++)
        {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            y[index] = y1;
            line[index].x = x1;
            line[index].y_down = y1;
            line[index].y_up = y2;
            line[index].flag = 1; //1表示左边

            index++;
            y[index] = y2;
            line[index].x = x2;
            line[index].y_down = y1;
            line[index].y_up = y2;
            line[index].flag = -1; //-1表示右边
            index++;
        }
        sort(&y[1], &y[index]); //把所有的纵坐标按从小到大排序,把1写成了0，WA一次
        sort(&line[1], &line[index]);
        build(1, 1, index-1);
        double ans=0;
        for (int i=1;i<index; i++)
        {
            ans += insert(1, line[i].x, line[i].y_down, line[i].y_up, line[i].flag);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", ++count, ans);
    }
    return 0;
}
