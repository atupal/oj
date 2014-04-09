
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>

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

void swapp(int a, int b ) {
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
        int t = heap[cur];
        heap[cur] = heap[largest];
        heap[largest] = t;
        max_heap(largest);
    }
}

int pop() {
    int tmp = heap[1];
    swapp(heap[0], 1);
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
        for (int tsum = 0, i = 0; tsum < sum;++i, left_cnt++, tsum += heap[i]);
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
    get(cur + 1, cnt + 1, 1);
    if (!sure[cur + 1])
        get(cur + 1, cnt, 0);
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

