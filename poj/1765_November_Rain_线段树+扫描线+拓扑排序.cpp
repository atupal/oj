/**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#define lson (root<<1)
#define rson (root<<1|1)
using namespace std;

//#define DEBUG

inline
long long min(long long a, long long b) {
  return a < b ? a : b;
}
inline
long long max(long long a, long long b) {
  return a > b ? a : b;
}

const long long maxn = 400100;
long long n;
long long x[maxn*2];
long long ans[maxn];
long long xn;

struct Point {
  long long x, y;
  long long type;
  long long ind;
  void print() {
    printf("%lld %lld\n", x, y);
  }
} p[maxn<<1];

struct Seg {
  long long x1, y1, x2, y2;
} seg[maxn];

long long degree[maxn];
long long sorted_seg[maxn];
long long cnt;
long long queue[maxn*2], head=0, tail=-1;
long long isolate[maxn];
long long isolate_cnt=0;

long long cmp1(const Point a, const Point b) {
  if (a.x != b.x) {
    return a.x < b.x;
  }
  return a.y < b.y;
}

long long cmp(const Seg a, const Seg b) {
  if (max(a.x1, b.x1) > min(a.x2, b.x2)) {
    return 0;
  }
  long long x = a.x2;
  long long y = a.y2;
  if (a.x1 >= b.x1 && a.x1 <= b.x2) {
    x = a.x1;
    y = a.y1;
  }
  double c = (double)(b.y2 - b.y1) / (b.x2 - b.x1) * (x - b.x1) + b.y1 * 1.0;
  return y - c > 0.;
}

long long cmp2(const Seg a, const Seg b, int x) {
  double c1 = (double) (a.y2 - a.y1) / (a.x2 - a.x1) * (x - a.x1) + a.y1 * 1.0;
  double c2 = (double) (b.y2 - b.y1) / (b.x2 - b.x1) * (x - b.x1) + b.y1 * 1.0;
  return c1 > c2;
}

// tree 保存区间雨量，tree2 保存点雨量
static struct {
  long long left;
  long long right;
  long long sum;
  long long mask;
  long long flag;
} tree[maxn*4+10], tree2[maxn*4+10];

void build(long long root, long long left, long long right) {
  tree[root].left = x[left-1];
  tree[root].right = x[right];
  tree[root].sum = x[right] - x[left-1];
  tree[root].mask = 0;
  tree[root].flag = 0;
  if (left == right) {
    tree[root].flag = 1;
    return;
  }
  long long mid = (left + right) >> 1;
  build(lson, left, mid);
  build(rson, mid+1, right);
}

void build2(long long root, long long left, long long right) {
  tree2[root].left = x[left];
  tree2[root].right = x[right];
  tree2[root].sum = 0;
  if (left == right) {
    return;
  }
  long long mid = (left + right) >> 1;
  build2(lson, left, mid);
  build2(rson, mid+1, right);
}

#define push(root) \
    tree[root].sum = 0;\
    tree[root].mask = 1;\

void push_down(long long root) {
  if (tree[root].flag) return;
  if (tree[root].mask) {
    push(lson);
    push(rson);
    tree[root].mask = 0;
  }
}

void push_down2(long long root) {
  if (tree2[root].left == tree2[root].right) return;
  if (tree2[root].mask) {
    tree2[lson].sum = 0;
    tree2[rson].sum = 0;
    tree2[lson].mask = -1;
    tree2[rson].mask = -1;
    tree2[root].mask = 0;
  }
}

void update(long long root) {
  tree[root].sum = tree[lson].sum + tree[rson].sum;
}

void update2(long long root) {
  tree2[root].sum = tree2[lson].sum + tree2[rson].sum;
}

void insert(long long root, long long left, long long right) {
  if (left <= tree[root].left && tree[root].right <= right) {
    push(root);
    return;
  } else if (tree[root].left >= right || tree[root].right <= left) {
    return;
  }
  push_down(root);
  insert(lson, left, right);
  insert(rson, left, right);
  update(root);
}

void insert2(long long root, long long left, long long right, long long c) {
  if (left <= tree2[root].left && tree2[root].right <= right) {
    if (c == -1) {
      tree2[root].mask = -1;
      tree2[root].sum = 0;
    } else {
      tree2[root].sum += c;
    }
    return;
  } else if (tree2[root].left > right || tree2[root].right < left) {
    return;
  }
  push_down2(root);
  insert2(lson, left, right, c);
  insert2(rson, left, right, c);
  update2(root);
}

/*
   debug 会发现，当有 （1 3 2 2）, （1,2,2,1） 这样的屋檐时不行。
 */
//void turn_left(long long root, long long left, long long c) {
//  if (tree[root].flag && tree[root].right == left) {
//    tree[root].sum += c;
//    return;
//  } else if (tree[root].left >= left || tree[root].right < left) {
//    return;
//  }
//  if (!tree[root].flag) {
//    push_down(root);
//    turn_left(lson, left, c);
//    turn_left(rson, left, c);
//    update(root);
//  }
//}
//
//void turn_right(long long root, long long right, long long c) {
//  if (tree[root].flag && tree[root].left == right) {
//    tree[root].sum += c;
//    return;
//  } else if (tree[root].left > right || tree[root].right <= right) {
//    return;
//  }
//  if (!tree[root].flag) {
//    push_down(root);
//    turn_right(lson, right, c);
//    turn_right(rson, right, c);
//    update(root);
//  }
//}

long long query(long long root, long long left, long long right) {
  if (left <= tree[root].left && tree[root].right <= right) {
    return tree[root].sum;
  } else if (tree[root].left >= right || tree[root].right <= left) {
    return 0;
  }
  push_down(root);
  return query(lson, left, right) + query(rson, left, right);
}

long long query2(long long root, long long left, long long right) {
  push_down2(root);
  if (left <= tree2[root].left && tree2[root].right <= right) {
    return tree2[root].sum;
  } else if (tree2[root].left > right || tree2[root].right < left) {
    return 0;
  }
  return query2(lson, left, right) + query2(rson, left, right);
}

struct Edge{
  long long dest;
  Edge *next;
} *edge[maxn];

void add_edge(long long ind, long long dest) {
  Edge *tmp = (Edge*) malloc (sizeof(Edge));
  tmp->dest = dest;
  tmp->next = edge[ind];
  edge[ind] = tmp;
}


void print_queue() {
  for (long long i = head; i <= tail; ++ i) {
    printf("%lld ", queue[i]);
  }
  printf("\n");
}

void pop(long long ind) {
  long long i;
  for (i = head; i <= tail; ++ i) {
    if (queue[i] == ind) {
      break;
    }
  }

  if (i-1 >= head) {
    add_edge(queue[i-1], ind);
#ifdef DEBUG
    printf("%lld -> %lld\n", queue[i-1], ind);
#endif
  }
  if (i+1 <= tail) {
    add_edge(ind, queue[i+1]);
#ifdef DEBUG
    printf("%lld -> %lld\n", ind, queue[i+1]);
#endif
  }
  if (i == head && i == tail) {
    isolate[isolate_cnt++] = ind;
  }

  for (long long x = i-1; x >= head; -- x) {
    queue[x+1] = queue[x];
  }

  ++ head;
#ifdef DEBUG
  printf("pxxxoxp %lld: ", ind);
  print_queue();
#endif
}

void add(long long ind) {
  for (long long x = head; x <= tail; ++ x) if (queue[x] == ind) return;
  long long i = head;
  while (i <= tail && cmp2(seg[queue[i]], seg[ind], seg[ind].x1)) ++ i;
  ++ tail;
  for (long long x = tail; x > i; -- x) {
    queue[x] = queue[x-1];
  }
  queue[i] = ind;
#ifdef DEBUG
  printf("axdxxd %lld: ", ind);
  print_queue();
#endif
}

void topo_sort() {
  memset(degree, 0, sizeof(degree));
  cnt = 0;
  Edge *l;
  for (long long i = 0; i < n; ++ i) {
    l = edge[i];
    while (l) {
      degree[l->dest] ++;
      l = l->next;
    }
  }
  long long top = -1;
  for (long long i = 0; i < n; ++ i) {
    if (degree[i] == 0) {
      degree[i] = top;
      top = i;
    }
  }
  for (long long i = 0; i < n; ++ i) {
    if (top == -1) {
      return;
    } else {
      sorted_seg[cnt++] = top;
      l = edge[top];
      top = degree[top];
      while (l) {
        if (--degree[l->dest] == 0) {
          degree[l->dest] = top;
          top = l->dest;
        }
        l = l->next;
      }
    }
  }
}

void solve() {
  head = 0;
  tail = -1;
  isolate_cnt = 0;
  memset(ans, 0, sizeof(ans));
  build(1, 1, xn);
  build2(1, 0, xn);
  memset(edge, 0, sizeof(edge));
  for (long long i = 0; i < n*2; ++ i) {
    if (p[i].type == -1) {
      add(p[i].ind);
    } else {
      long long x = i+1;
      while (x < n*2 && p[x].x == p[i].x && p[x].type == -1) {
        add(p[x].ind);
        ++ x;
      }
      pop(p[i].ind);
    }
  }
  topo_sort();
  for (long long i = 0; i < n; ++ i) {
    long long ind;
    if (i < cnt)
      ind = sorted_seg[i];
    else
      ind = isolate[i-cnt];
#ifdef DEBUG
    printf("%lld: (%lld, %lld), (%lld, %lld)\n", ind, seg[ind].x1, seg[ind].y1, seg[ind].x2, seg[ind].y2);
#endif
    ans[ind] = query(1, seg[ind].x1, seg[ind].x2);
    long long tmp = query2(1, seg[ind].x1, seg[ind].x2);
    ans[ind] += tmp;
    insert(1, seg[ind].x1, seg[ind].x2);
    insert2(1, seg[ind].x1, seg[ind].x2, -1);
    if (seg[ind].y1 < seg[ind].y2) {
      insert2(1, seg[ind].x1, seg[ind].x1, ans[ind]);
    } else {
      insert2(1, seg[ind].x2, seg[ind].x2, ans[ind]);
    }
  }

  for (long long i = 0; i < n; ++ i) {
    printf("%lld\n", ans[i]);
  }
}

int main() {
  while(scanf("%lld", &n) != EOF) {
    for (long long i = 0; i < n; ++ i) {
      //scanf("%d %d %d %d", &seg[i].x1, &seg[i].y1, &seg[i].x2, &seg[i].y2);
      scanf("%lld %lld %lld %lld", &p[i<<1].x, &p[i<<1].y, &p[i<<1|1].x, &p[i<<1|1].y);
      seg[i].x1 = p[i<<1].x, seg[i].y1 = p[i<<1].y;
      seg[i].x2 = p[i<<1|1].x, seg[i].y2 = p[i<<1|1].y;
      p[i<<1].ind = i, p[i<<1].type = -1;
      p[i<<1|1].ind = i, p[i<<1|1].type = 1;
      x[i<<1] = p[i<<1].x;
      x[i<<1|1] = p[i<<1|1].x;
    }

    sort(x, x+2*n);
    long long i = 0, j = 1;
    while (j < 2*n) {
      while (j < 2*n && x[j]==x[i]) ++ j;
      if (j < 2*n) x[++i] = x[j];
    }
    xn = i;

    //sort(seg, seg+n, cmp);
    sort(p, p+2*n, cmp1);
    solve();
    printf("\n");
  }

  return 0;
}

/*
   由于 poj 过滤这个代码中的某些可能为住入的字符，所以导致不能提交。但在 spoj 上已经过了。
   请提交下面的 代码：

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
    int t;
    scanf("%d", &t);
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
    }
    return 0;
}
 */
