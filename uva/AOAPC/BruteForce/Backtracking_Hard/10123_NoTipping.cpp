
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxn = 101;

struct node{
    int index;
    int pos;
    int wei;
    double torl;
    double torr;
}pl[maxn], pr[maxn];

int Len, Wei, n;
double torl[maxn], torr[maxn];
char ans;
char v[maxn];
int B[maxn];
int V[maxn];
int cnt;
int nl;
int nr;

int cmpl(const void *a, const void *b) {
    return ((node*)a)->torl - ((node*)b)->torl;
}

int cmpr(const void *a, const void *b) {
    return ((node*)a)->torr - ((node*)b)->torr;
}

int dfs(int cur, double left, double right) {
    int isleft = 1, isright = 1;
    int flag;
    if (cur == n) {
        return 2;
    }
    for (int i = 0; i < nl; ++ i) if (!v[pl[i].index]){
        v[pl[i].index] = 1;
        B[cur] = pl[i].index;
        if (left + pl[i].torl <= 0)
            isleft = 0;
        if (left + pl[i].torl <= 0 && right + pl[i].torr <= 0) {
            flag = dfs(cur + 1, left + pl[i].torl, right + pl[i].torr);
            if (flag == 2)
                return 2;
            if (flag == -1) 
                break;
        }
        v[pl[i].index] = 0;
    }

    for (int i = 0; i < nr; ++ i) if (!v[pr[i].index]) {
        v[pr[i].index] = 1;
        B[cur] = pr[i].index;
        if (right + pr[i].torr <= 0) 
            isright = 1;
        if (left + pr[i].torl <= 0 && right + pr[i].torr <= 0) {
            flag = dfs(cur + 1, left + pr[i].torl, right + pr[i].torr);
            if (flag == 2)
                return 2;
            if (flag == 1)
                break;
        }
        v[pr[i].index] = 0;
    }
    return isright - isleft;
}

int main() {
    cnt = 0;
    while (scanf("%d%d%d", &Len, &Wei, &n)) {
        ++ cnt;
        if (Len + Wei + n == 0) return 0;
        nl = nr = 0;
        int pos[maxn],wei[maxn];
        int cur = 0;
        memset(v, 0, sizeof(v));
        double left = -Wei * 3.0;
        double right = -Wei * 3.0;
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &pos[i], &wei[i]);
            pos[i] *= 2;
            if (pos[i] < -3){
                pl[nl ++].pos = pos[i];
                pl[nl - 1].torl = (double)wei[i] * (-pos[i] - 3.0);
                pl[nl - 1].torr = (double)wei[i] * (-pos[i] + 3.0) * -1;
                pl[nl - 1].index = i;
            }
            else if(pos[i] > 3) {
                pr[nr ++].pos = pos[i];
                pr[nr - 1].torr = (double)wei[i] * (pos[i] - 3.0);
                pr[nr - 1].torl = (double)wei[i] * (pos[i] + 3.0) * -1;
                pr[nr - 1].index = i;
            }
            else {
                v[i] = 1;
                B[cur ++] = i;
                left += (double)wei[i] * (pos[i] + 3.0) * -1;
                right += (double)wei[i] * (3.0 - pos[i]) * -1;
            }
        }
        qsort(pl, nl, sizeof(node), cmpl);
        qsort(pr, nr, sizeof(node), cmpr);
        ans = dfs(cur, left, right);
        printf("Case %d:\n", cnt);
        if (ans != 2) printf("Impossible\n");
        else {
            //qsort(p, n, sizeof(node), cmpi);
            for (int i = n - 1; i >= 0; -- i) printf("%d %d\n", (int)(pos[B[i]] / 2.0), wei[B[i]]);
        }
    }

    return 0;
}




/*
UVA 10123 No Tipping
UVA_10123

    以下斜体部分是我第一次写的解题报告，但后来越来越觉得我实现的程序和我的想法并不怎么挂钩，于是就越发怀疑程序里那个剪枝的正确性了。

    再后来看了UVA的论坛之后，发现上面有人提到用记忆化搜索去解，我这时再一看N只有20，完全可以用状态压缩+记忆化搜索来做，只是当时没有想到，其中一部分原因也是觉得LRJ放在了回溯这章里面，就压根没向着dp的方向去考虑，一直在想怎么剪枝去了，便也凑巧，居然诞生了下面的我现在也不知道正确与否的回溯做法。以后千万不要局限于已知的这题的归类，换个思路也许就能海阔天空了。

    如果各位兄台谁有兴趣证明出了或者推翻了下面这个回溯的程序，还望能和小弟分享一下。当然，这个回溯程序在UVA上是能AC的，而且跑得很快，但我后来总觉得这个程序的剪枝有问题。

    下面还是说一下dp的思路吧。由于N不大，2的20次方也就10^6左右，因此可以把所有木块的状态用2进制表示出来，于是可以用f[i]表示是否可以达到木块的状态为i的这种状态。接下来我们既可以一个一个地向上放，也可以一个一个地向下拿，只要看最后起始状态的f[st]是否为1即可。

    “首先，我们如果考虑怎么拿的话会比较麻烦，不如我们反过来考虑怎么放，如果每个时刻放的都能平衡，那么最后就能得出一个可行解。

    “但是如果直接回溯的话会超时，我们不妨慢慢来优化算法。

    “第一，最好把坐标先乘2化成整数，这样就避免了浮点数误差。

    “第二，我们在放的时候，一个贪心思路就是先把两个支点中间的木块放上，比较容易证明这样只会增加后续木板的稳定程度。

    “第三，我们应该把其余的木块按力矩大小降序排序，支点是离它最近的那个支点，先选力矩小的，这样一定程度上减少了木板弄翻的可能。

    “第四，上面的按力矩排序还带来了额外的好处，我们不妨用两个数组分别存左边和右边的待放的木块。我们先考虑右边的，假设我们现在放了一个木块上去，结果发现后面无论怎么放木板都会右翻，显然就不用再尝试这个木块右边的木块了，因为必然也会右翻。同样，对于左边的木块，假设我们现在放了一个木块上去，结果发现后面无论怎么放木板都会左翻，显然就不用再尝试这个木块左边的木块了，因为必然也会左翻。当然，如果后续可能左翻也可能右翻的话就要继续尝试剩余的木块。

    “考虑完上面几点之后就可以AC了。”


//深搜剪枝，回溯
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXD 30
int L, N, W, s[MAXD], r1[MAXD], r2[MAXD], N1, N2, x[MAXD], w[MAXD], vis[MAXD];
int cmp(const void *_p, const void *_q)
{
    int *p = (int *)_p;
    int *q = (int *)_q;
    int x1 , x2;
    if(x[*p] < 0)
        x1 = (-3 - x[*p]) * w[*p];
    else
        x1 = (x[*p] - 3) * w[*p];
    if(x[*q] < 0)
        x2 = (-3 - x[*q]) * w[*q];
    else
        x2 = (x[*q] - 3) * w[*q];
    return x1 - x2;
}
void init()
{
    int i;
    for(i = 0; i < N; i ++)
    {
        scanf("%d%d", &x[i], &w[i]);
        x[i] *= 2;
    }
}
int dfs(int left, int right, int num)
{
    int i, j, k, t, flag, mleft, mright, tleft = 1, tright = 1;
    if(num == N)
        return 2;
    for(i = 0; i < N1; i ++)
    {
        k = r1[i];
        if(!vis[k])
        {
            vis[k] = 1;
            mleft = left + (x[k] + 3) * w[k], mright = right + (3 - x[k]) * w[k];
            s[num] = k;
            if(mleft >= 0)
                tleft = 0;
            if(mleft >= 0 && mright >= 0)
            {
                flag = dfs(mleft, mright, num + 1);
                if(flag == 2)
                    return 2;
                if(flag == -1)
                    break;
                tleft = 0;
            }
            vis[k] = 0;
        }
    }
    for(i = 0; i < N2; i ++)
    {
        k = r2[i];
        if(!vis[k])
        {
            vis[k] = 1;
            mleft = left + (x[k] + 3) * w[k], mright = right + (3 - x[k]) * w[k];
            s[num] = k;
            if(mright >= 0)
                tright = 0;
            if(mleft >= 0 && mright >= 0)
            {
                flag = dfs(mleft, mright, num + 1);
                if(flag == 2)
                    return 2;
                if(flag == 1)
                    break;
                tright = 0;
            }
            vis[k] = 0;
        }
    }
    return tright - tleft;
}
void solve()
{
    int i, j, k, left, right, num;
    memset(vis, 0, sizeof(vis));
    num = 0;
    left = right = 3 * W;
    for(i = 0; i < N; i ++)
        if(x[i] >= -3 && x[i] <= 3)
        {
            s[num ++] = i;
            vis[i] = 1;
            left = left + (x[i] + 3) * w[i], right = right + (3 - x[i]) * w[i];
        }
    N1 = N2 = 0;
    for(i = 0; i < N; i ++)
        if(!vis[i])
        {
            if(x[i] < 0)
                r1[N1 ++] = i;
            else
                r2[N2 ++] = i;
        }
    qsort(r1, N1, sizeof(r1[0]), cmp);
    qsort(r2, N2, sizeof(r2[0]), cmp);
    if(dfs(left, right, num) != 2)
        printf("Impossible\n");
    else
    {
        for(i = N - 1; i >= 0; i --)
            printf("%d %d\n", x[s[i]] / 2, w[s[i]]);
    }
}
int main()
{
    int t = 0;
    for(;;)
    {
        scanf("%d%d%d", &L, &W, &N);
        if(!L)
            break;
        init();
        printf("Case %d:\n", ++ t);
        solve();
    }
    return 0;
}

 


//状态压缩+记忆化搜索
#include<stdio.h>
#include<string.h>
#define MAXD 1100000
#define MAXN 25
int N, L, W, x[MAXN], w[MAXN];
int f[MAXD], left[MAXD], right[MAXD];
void init()
{
    int i;
    for(i = 0; i < N; i ++)
    {
        scanf("%d%d", &x[i], &w[i]);
        x[i] *= 2;
    }
}
int dp(int st)
{
    int i, k, mleft, mright;
    if(f[st] != -1)
        return f[st];
    if(st == 0)
        return f[st] = 1;
    for(i = 0; i < N; i ++)
        if((1 << i) & st)
        {
            mleft = left[st] + (x[i] + 3) * w[i];
            mright = right[st] + (3 - x[i]) * w[i];
            if(mleft >= 0 && mright >= 0)
            {
                k = st ^ (1 << i);
                left[k] = mleft, right[k] = mright;
                if(dp(k))
                {
                    printf("%d %d\n", x[i] / 2, w[i]);
                    return f[st] = 1;
                }
            }
        }
    return f[st] = 0;
}
void solve()
{
    int i, st;
    memset(f, -1, sizeof(f));
    st = (1 << N) - 1;
    left[st] = W * 3, right[st] = W * 3;
    if(!dp(st))
        printf("Impossible\n");
}
int main()
{
    int t = 0;
    for(;;)
    {
        scanf("%d%d%d", &L, &W, &N);
        if(!L)
            break;
        init();
        printf("Case %d:\n", ++ t);
        solve();
    }
    return 0;
}
*/

/*
这个题纠结了好久。首先想到的是暴搜，必超时。
    然后注意到题目中，天平左边的物体和右边的物体交替取，可能会使更快得到最优解，所以就根据他们的位置是否>0把他们放到两个数组里，这里有个优化就是按照到达-1.5和+1.5的力矩排序，这样如果取了前面的物体天平失去了平衡，则后面的物体也不用取了，一定会失去平衡。这样继续暴搜，还是超时。我估计这个优化没什么用，因为就算你把剩下的都取完，也不需要浪费多少时间嘛。。。平均意义上能减少一般的时间。但是A(20,20)。。这个有点大。
     好吧，又继续陷入僵局了。看别人的结题报告，发现主流版本是一堆乱糟糟的代码，不懂在搞什么。。。后来偶然发现了一个版本，在暴搜的时候，写的很奇怪，参见http://blog.csdn.net/wuli2496/article/details/7284641。dfs(l,r)，l,r表示前面l-1,r-1个已经取过了，这让我煞是费解。（他的解法是把物体一个个的放到纠结的天平上），为什么不能先力矩放大的，后放力矩小的？然后我改了下他的dfs()，变成无参的，每次都从0开始找，交，超时了。作者没有说明他为什么要这么做，或许是他不想说？或者他没留意？而且这明明就不是个dfs了，如果可以证明，先放小的比先放大的好，那么这个dfs就是个DP了。和有限背包问题一样的。好吧。然后我就想着证明为何先放力矩小的比先放力矩大的好，想了很久，发现，没办法。
    后来，偶然想到了一种方法，证明出如果在当前的情况中，拿掉左边力矩最大的，天平向右歪，并且拿掉右边力矩最大的，天平向左歪，那么无论以后怎么拿，都不可能成功。
    这样反推一下，刚刚好是一个dp。r[i][j]表示放上去了左边前i个，右边前j个的天平状况（这种状况刚刚好依赖于0-i,0-j的质量）。它只能由r[i][j-1],r[i-1][j]推出。
    额，这样就是一个完美的背包问题了，只要20*20个状态，交了，A掉了，跑的足够快，理论上应该是最快的解法了吧？肯定比搜索快，也要比状态压缩的DP快，因为状态压缩的DP需要2^20个状态。。。可能是我的代码写的太乱了，所以才跑到15名。。
    好了，最重要的的问题就是证明上面一段中红色字的结论。
    现在我们把天平分成3段：第一段是最左边到-1.5，中间是-1.5到1.5，右边是1.5-最右边。
    左边的物体的力矩我们记为:WL(左边最大那个力矩) + Lrest(左边剩余力矩) ,中间的物体的力矩我们记为 C+Mrest(C表示中间那一段的模板质量，Mrest表示中间物体质量),右边的力矩我们记为
 WR(右边最大那个力矩)+Rrest(右边剩余力矩)。我们可以简单地在左边和右边都剪掉Rrest。那么左边，中间，右边的力矩为WL+rest, C+Mrest,WR。如果拿掉左边最大的右偏，我们可以得到式子 : rest + C + Mrest < WR 。那么很显然，rest会越来越小，所以这个式子永远成立，所以红字得证。
好了，这个证明想了很久，而且中间用到了一个结论：拿掉天平左右两边等重的物体，对天平没影响。对于有两个平衡点的这只是个臆测，额好吧，谁有更好更简单的解法欢迎交流。LRJ出的题果真很神，不过也很让人纠结。代码写的比较乱，莫看。
#include <cstdio>
#include <cstdlib>
#include <cstring>

class node
{
  public:
    int pos,w;
};

class set
{
 public:
   int ll,lr,rl,rr;
   int prev,ok;
};

set res[30][30];

node lefts[110],rights[110];
int lcount,rcount;
int find;
int L,W,C;

int abs(int i)
{
  if(i>0) return i;
  return -i;
}

void pans(int l,int r)
{
  if(l == 0 && r== 0)
    return;
  if(res[l][r].prev == 1)
  {
    printf("%d %d\n",rights[r-1].pos/2,rights[r-1].w);
    pans(l,r-1);
  }
  else
  {
    printf("%d %d\n",lefts[l-1].pos/2,lefts[l-1].w);
    pans(l-1,r);
  }
}
int cmp1(const void* a,const void* b)
{
  node i = *(node*)a;
  node j = *(node*)b;
  return (-i.pos-3)*i.w - (-j.pos-3)*j.w;
}

int cmp2(const void* a,const void* b)
{
  node i = *(node*)a;
  node j = *(node*)b;
  return (i.pos-3)*i.w - (j.pos-3)*j.w;
}


int main()
{
   //freopen("in.txt","r",stdin);
   //freopen("out.txt","w",stdout);
   int i,c=1,j; 
   int ll,lr,rl,rr;
   while(scanf("%d%d%d",&L,&W,&C)!=EOF && L>0)
   {
     memset(res,0,sizeof(res));
     L *= 2;
     ll = rr =0; rl = lr = 3*W;
     node tmp; 
     lcount = rcount = 0;
     for(i=0;i<C;i++)
     {
       scanf("%d%d",&tmp.pos,&tmp.w);
       tmp.pos*=2;
      if(tmp.pos<0)
         lefts[lcount++] = tmp;
       else
         rights[rcount++] = tmp;
     }
     qsort(lefts,lcount,sizeof(node),cmp1);
     qsort(rights,rcount,sizeof(node),cmp2);
     
     set tmpset = {ll,lr,rl,rr,0,1};
     res[0][0] = tmpset;
     for(i=0;i<=lcount;i++)
      for(j=0;j<=rcount;j++)
      {
        if(i-1>=0 && res[i-1][j].ok == 1)
            {
                  tmpset = res[i-1][j];
                  //放了第i个物体
                 if(lefts[i-1].pos < -3)
                   tmpset.ll += (-3-lefts[i-1].pos)*lefts[i-1].w; 
                 else
                   tmpset.lr += (lefts[i-1].pos+3)*lefts[i-1].w;
                 if(lefts[i-1].pos < 3)
                   tmpset.rl += (3 - lefts[i-1].pos)*lefts[i-1].w;
                 else
                   tmpset.rr += (lefts[i-1].pos - 3)*lefts[i-1].w;
                 if(tmpset.ll < tmpset.lr && tmpset.rl>tmpset.rr)
                 {
                    tmpset.ok = 1;
                    tmpset.prev = -1;
                    res[i][j] = tmpset;
                 }
                 else
                   {
                     res[i][j].ok = 0;
                 }
            }
              
              
         if(res[i][j].ok) 
              continue;
         if(j-1>=0 && res[i][j-1].ok == 1)
            {
              tmpset = res[i][j-1];
               if(rights[j-1].pos < -3)
                 tmpset.ll += (-3-rights[j-1].pos)*rights[j-1].w; 
               else
                 tmpset.lr += (rights[j-1].pos+3)*rights[j-1].w;
               if(rights[j-1].pos < 3)
                 tmpset.rl += (3 - rights[j-1].pos)*rights[j-1].w;
               else
                 tmpset.rr += (rights[j-1].pos - 3)*rights[j-1].w;
              if(tmpset.ll < tmpset.lr && tmpset.rl>tmpset.rr)
                 {
                    tmpset.ok = 1;
                    tmpset.prev = 1;
                    res[i][j] = tmpset;
                 }
                 else
                   {
                     res[i][j].ok = 0;
                 }
            }                      


      }
      printf("Case %d:\n",c++);
       if(res[lcount][rcount].ok == 1)
         pans(lcount,rcount);
       else
        printf("Impossible\n");
   }
   return 0;
}
*/
