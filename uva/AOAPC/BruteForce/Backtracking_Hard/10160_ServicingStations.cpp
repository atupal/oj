/*
 * 实质是求图的最小支配集顶点个数,是NP问题,只能枚举?
 * 给你一个一个图,选出一个顶点集合使得每个顶点要么在这个集合中要么与这个集合中的某个顶点相邻
 * 先考虑枚举顺序:从度数大的顶点开始
 * 剪枝:1,最优解性剪枝,若比当前的最优解要坏就提前回溯
 * 2,估计剩下没有枚举的点中最少要几个点才能覆盖全图
 * 3,若某个顶点不管以后怎么枚举都不可能覆盖就提前回溯
 * 优化:2的那个剪枝是用qsort实现的,改成堆应该会更快
 *
 * ps:网上有人用精确覆盖做的, X算法,跳舞连,高纳德发明的....
 * ps:一开始的枚举方法是枚举取点的顺序,不管怎么优化都很慢,后来画出解答树一看这样是枚举了整个排列...果断直接枚举1到n个点...
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

const int maxn = 101;

int n,m;
vector<int> G[maxn];
int ans;
int v[maxn];
int V[maxn];
int has[maxn];
int cnt[maxn];
int order[maxn];
int tv[maxn];
int dfs_cnt;
int pre[maxn][maxn];
int sure[maxn];
int heap[10];


int cmp(const void *a, const void *b) {
    return cnt[*((int*)b)] - cnt[*((int*)a)];
}

int cmpt(const void *a, const void *b) {
    return *((int*)b) - *((int*)a);
}

void dfs(int cur) { 
    if (ans != n) return;
    int flag = 0;
    for (int i = 1; i <= n; ++ i) if (!has[i]) {
        flag = 1;
        break;
    }
    if (cur >= ans) 
        return;
    if (!flag) {
        ans = cur;
        return;
    }
    for (int i = 0; i < n; ++ i) {
        int node = order[i];
        if (!v[node] && (!has[node] || (has[node] && cnt[node] > 3))){
            v[node] = 1;
            if (!has[node])
                has[node] = node;
            for (int x = 0; x < (int)G[node].size(); ++ x) if (!has[G[node][x]])
                has[G[node][x]] = node;
            dfs(cur + 1);
            if (has[node] == node) 
                has[node] = 0;
            for (int x = 0; x < (int)G[node].size(); ++ x) if (has[G[node][x]] == node) 
                has[G[node][x]] = 0;
            v[node] = 0;
        }
    }
    for (int i = 0; i < n; ++ i) {
        int node = order[i];
        if (!v[node] && !(!has[node] || (has[node] && cnt[node] > 3))){
            v[node] = 1;
            if (!has[node])
                has[node] = node;
            for (int x = 0; x < (int)G[node].size(); ++ x) if (!has[G[node][x]])
                has[G[node][x]] = node;
            dfs(cur + 1);
            if (has[node] == node) 
                has[node] = 0;
            for (int x = 0; x < (int)G[node].size(); ++ x) if (has[G[node][x]] == node) 
                has[G[node][x]] = 0;
            v[node] = 0;
        }
    }
}

void dfscnt(int cur) {
    for (int i = 0; i < (int)G[cur].size(); ++ i) if (!tv[G[cur][i]]) {
        tv[G[cur][i]] = 1;
        dfscnt(G[cur][i]);
    }
}

void clear(int cur) {
    if (has[cur] == cur) 
        has[cur] = 0;
    for (int i = 0; i < (int)G[cur].size(); ++ i) if (has[G[cur][i]] == cur) 
        has[G[cur][i]] = 0;
    v[cur] = 0;
}

void map(int cur) {
    if (!has[cur]) 
        has[cur] = cur;
    for (int i = 0; i < (int)G[cur].size(); ++ i) if (!has[G[cur][i]]) 
        has[G[cur][i]] = cur;
}

void swap(int a, int b ) {
    int t = heap[a];
    heap[a] = heap[b];
    heap[b] = t;
}

void max_heap(int cur) {
    int l = cur << 1;
    int r = l + 1;
    int largest;
    if (l <= heap[0] && heap[l] > heap[cur]) 
        largest = l;
    else largest = cur;
    if (r <= heap[0] && heap[r] > heap[largest])
        largest = r;
    if (largest != cur) {
        swap(cur, largest);
        max_heap(largest);
    }
}

int pop() {
    int tmp = heap[1];
    swap(heap[0], 1);
    heap[0] --;
    max_heap(1);
    return tmp;
}


void get(int cur, int cnt, int isnot) {
    if (cur == n + 1) return;
    int flag = 0;
    if (isnot) {
        v[cur] = 1;
        map(cur);

        int left_cnt = 0;
        /***************/
        for (int i = cur + 1; i <= n; ++ i)
            heap[i - cur - 1] = G[i].size() + 1;
        qsort(heap, n - cur, sizeof(int), cmpt);
        int sum = 0;
        for (int i = 1; i <=n; ++ i) if (!has[i]) 
            sum ++;
        for (int tsum = 0, i = 0; tsum < sum && i < n - cur;++i, left_cnt++, tsum += heap[i]);
        /***************/
        /***************/
        //heap[0] = 0;
        //for (int i = cur + 1; i <= n; ++ i)
        //    heap[++heap[0]] = G[i].size() + 1;
        //int sum = 0;
        //for (int i = 1; i <=n; ++ i) if (!has[i]) 
        //    sum ++;
        //for (int i = heap[0] / 2; i > 0; -- i)
        //    max_heap(i);
        //int t = heap[0];
        //for (int tsum = 0, i = 0; tsum < sum && i < t; ++ i,++ left_cnt, tsum += pop());
        /***************/
        for (int i = 1; i <= n; ++ i) if (!has[i])
            flag = 1;
        if (cnt + left_cnt >= ans) {
            clear(cur);
            return;
        }
        if (!flag) {
            ans = cnt;
            memcpy(V, v, sizeof(v));
            clear(cur);
            return;
        }
        for (int i = 1; i < cur; ++ i) if (!has[i] && pre[i][maxn - 1] <= cur) {
            clear(cur);
            return;
        }
        else if (!has[i] && pre[i][cur] == 1) {
            sure[pre[i][maxn - 1]] = cur;
        }

    }
    if (!sure[cur + 1])
        get(cur + 1, cnt, 0);
    get(cur + 1, cnt + 1, 1);
    if (isnot) {
        clear(cur);
    }
    for (int i = 1; i <= n; ++ i) if (sure[i] == cur) 
        sure[i] = 0;
}

int main() {
    int x, y;
    while (scanf("%d %d", &n, &m)) {
        if (!n) return 0;
        for (int i = 1; i <= n; ++ i) G[i].clear();
        memset(v, 0, sizeof(v));
        memset(has, 0, sizeof(has));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < m; ++ i) {
            scanf("%d %d", &x, &y);
            G[x].push_back(y);
            G[y].push_back(x);
            cnt[x] ++;
            cnt[y] ++;
        }
        memset(sure, 0, sizeof(sure));
        memset(pre, 0 ,sizeof(pre));
        for (int i = 1; i <= n; ++ i) {
            int max = i;
            for (int j = 0; j < (int)G[i].size(); ++ j) {
                if (G[i][j] > max) {
                    max = G[i][j];
                }
            }
            pre[i][maxn - 1] = max;
            for (int x = 0; x < (int)G[i].size(); ++ x)
                for (int y = 0; y < G[i][x]; ++ y)
                    pre[i][y] ++;
        }
        for (int i = 0; i < n; ++ i) 
            order[i] = i + 1;
        qsort(order, n, sizeof(int), cmp);
        ans = n;
        dfs(0);
        memset(v, 0, sizeof(v));
        memset(has, 0, sizeof(has));
        get(1, 0, 0);
        memset(v, 0, sizeof(v));
        memset(has, 0, sizeof(has));
        get(1, 1, 1);
        //for (int i = 1; i <= n; ++ i) if (V[i])
        //    printf("%d ", i);
        //printf("\n");
        printf("%d\n", ans);
    }
    return 0;
}

/*
// Servicing Stations （服务站）
// PC/UVa IDs: 110804/10160, Popularity: B, Success rate: low Level: 3
// Verdict: Accepted 
// Submission Date: 2011-08-10
// UVa Run Time: 0.056s

// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 该题目的实质是求图的最小支配集顶点个数。求图的最小支配集问题是 NP 完全问题，目前无高效的算法。
// 既然要枚举集合的所有子集，那就枚举吧，但是等一等，枚举需要个顺序，先枚举元素数量小的子集，要不
// 然，先枚举元素个数大的子集可能会浪费时间，毕竟从元素个数小的子集枚举到元素个数大的子集可以保证
// 找到最小支配集而不再浪费更多的时间，哎呀，时间是金钱，不是吗？可能什么时候某个强人发现 NP 难问
// 题的 P 时间算法，或者证明 P = NP 那就好了，希望在有生之年能够看到！！
//
// 为了提高效率，压缩程序运行时间，采用了以下优化方法：
// （1）若图可以拆分为多个不相连的子图，则先予拆分，然后对子图求最小支配集的顶点个数相加(之前由
//     于未拆分图，导致了多次 TLE）。
// （2）对于求两个集合的并采用了位操作，事先将某个顶点的邻接表表示为一个整数以便用与操作来代替集合
//     的并。
// （3）枚举时，先考虑度数大的顶点。
//
// 枚举方法参考了 [J. Loughry, J.I. van Hemert, L. Schoofs, Efficiently Enumerating
// the Subsets of a Set, 2000]

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define MAX_TOWN 35

typedef long long unsigned LLUINT;

bool finish;
int minimum;
vector < LLUINT > edge;
LLUINT target_tag, origin_tag;

// 检查顶点集合是否为支配集。
void check(int flag[], int position)
{
    int index = 0;
    LLUINT new_tag = origin_tag, old_tag = origin_tag;

    for (int i = 0; i < edge.size(); i++)
    {
        if ((index < position) && (flag[index] == i))
        {
            new_tag |= edge[i];
            if (new_tag > old_tag)
                old_tag = new_tag;
            else
                return;
            index++;
        }
    }
    
    if (new_tag == target_tag)
    {
        minimum = index;
        finish = true;
    }
}

// 按 Banker’s Sequence 枚举图的子集。
void generate(int flag[], int position, int positions)
{
    if (finish)
        return;

    if (position < positions)
    {
        if (position == 0)
        {
            for (int i = 0; i < edge.size(); i++)
            {
                flag[position] = i;
                generate(flag, position + 1, positions);
            }
        }
        else
        {
            for (int i = flag[position - 1] + 1; i < edge.size(); i++)
            {
                flag[position] = i;
                generate(flag, position + 1, positions);
            }
        }
    }
    else
        check(flag, position);
}

// 枚举图向量的子集以判断是否是一个支配集。
void enumerating_subset()
{
    for (int i = 1; i <= edge.size(); i++)
    {
        int * flag = new int[edge.size()];
        generate(flag, 0, i);
        delete [] flag;
        
        if(finish)
            return;
    }
}

bool cmp(LLUINT x, LLUINT y)
{
    return x > y;
}

// 获取图的最小支配集顶点数（MDSN）。
int mdsn(vector < vector < int > > &vertex)
{
    int base = 0;
    origin_tag = 0;
    target_tag = 0;
    
    vector < bool > dirty(vertex.size());
    fill(dirty.begin(), dirty.end(), false);
    
    // 清掉度为 0 的点。度为 0 的点和其他点都无通路，则该图的最小支配集必须要包括
    // 该顶点。则表示最小支配集顶点个数的变量 base 需增加 1。
    for (int i = 0; i < vertex.size(); i++)
    {
        if (vertex[i].size() == 0)
        {
            base++;
            origin_tag |= ((LLUINT)1 << i);
        }
        
        if (vertex[i].size() == 1 && dirty[i] == false)
        {
            dirty[i] = true;
            if (dirty[vertex[i][0] - 1] == false)
            {
                base++;
                dirty[vertex[i][0] - 1] = true;
            }
        }

        target_tag |= ((LLUINT)1 << i);
    }

    // 清掉度为 1 的点。度为 1 的点表明该顶点 A 只与其他一个顶点 B 相连接，则可
    // 将 B 计入最小支配集中。
    edge.clear();
    for (int i = 0; i < vertex.size(); i++)
    {
        if (dirty[i] == true)
        {
            origin_tag |= ((LLUINT)1 << i);
            for (int j = 0; j < vertex[i].size(); j++)
                origin_tag |= ((LLUINT)1 << (vertex[i][j] - 1));
        }
        
        if (dirty[i] == false && vertex[i].size() > 0)
        {
            LLUINT t = ((LLUINT)1 << i);
            for (int j = 0; j < vertex[i].size(); j++)
                t |= ((LLUINT)1 << (vertex[i][j] - 1));
            edge.push_back(t);
        }
    }
    
    // 排序，度数大的点首先考虑。
    sort(edge.begin(), edge.end(), cmp);
    
    minimum = 0;
    finish = false;
    enumerating_subset();
    
    return (base + minimum);
}

int servicing_stations(vector < vector < int > > &vertex)
{   
    // 使用宽度优先搜索分离子图，计算子图的最小支配集顶点个数，相
    // 加即为原图的最小支配集顶点个数。
    int total = 0;
    while (vertex.size() > 0)
    {
        vector < vector < int > > open;
        set < int > close;
        
        int size = 0;
        open.push_back(vertex[0]);
        
        close.insert(vertex[0][0]);
        vertex.erase(vertex.begin());
        
        while (open.size() > size)
        {
            int origin = size;
            int current = open.size() - 1;
            size = open.size();
            
            for (int i = origin; i <= current; i++)
            {
                for (int j = 1; j < open[i].size(); j++)
                {
                    if (close.find(open[i][j]) == close.end())
                    {
                        close.insert(open[i][j]);
                        for (int m = 0; m < vertex.size(); m++)
                        {
                            if (vertex[m][0] == open[i][j])
                            {
                                open.push_back(vertex[m]);
                                vertex.erase(vertex.begin() + m);
                                break;
                            }
                        }
                    }
                }
            }
        }
        
        // 调整分离出的子图的序号以便后续操作。
        vector < vector < int > > tmp;
        for (int c = 1; c <= MAX_TOWN; c++)
            if (close.find(c) != close.end())
            {
                for (int i = 0; i < open.size(); i++)
                    if (open[i][0] == c)
                        tmp.push_back(open[i]);
            }
        
        for (int i = 0; i < tmp.size(); i++)
        {
            int current = tmp[i][0];
            for (int m = 0; m < tmp.size(); m++)
                for (int n = 1; n < tmp[m].size(); n++)
                    if (tmp[m][n] == current)
                        tmp[m][n] = (i + 1);
        }
        
        for (int i = 0; i < tmp.size(); i++)
            tmp[i].erase(tmp[i].begin());
        
        // 计算该子图的最小支配集顶点数。
        total += mdsn(tmp);
    }
    
    return total;
}

int main(int ac, char *av[])
{
    int n;
    int m;
    int x, y;
    vector < vector < int > > vertex;
    
    while (cin >> n >> m, n && m)
    {
        vertex.clear();
        vertex.resize(n);
        
        // 数组的第一个数存放顶点的序号。
        for (int i = 0; i < n; i++)
            vertex[i].push_back((i + 1));
        
        // 读入镇之间的通路。
        for (int i = 0; i < m; i++)
        {
            // 自身连接到自身的通路不添加。
            cin >> x >> y;
            if (x != y)
            {
                vertex[x - 1].push_back(y);
                vertex[y - 1].push_back(x);
            }
        }
        
        cout << servicing_stations(vertex) << endl;
    }

    return 0;
}
*/
