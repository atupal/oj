#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
using namespace std;

const int maxn_step = 46656;
const int maxn = 666666;
int a, b;
int vis[maxn];

int input() {
    a = b = 0;
    int tmp[7];
    for (int i = 1; i <= 6; ++ i) {
        scanf("%d", tmp+i);
    }
    for (int i = 6; i; -- i) {
        a = a * 10 + tmp[i];
    }
    for (int i = 1; i <= 6; ++ i) {
        if (scanf("%d", tmp+i) == EOF) return 0;
    }
    for (int i = 6; i; -- i) {
        b = b * 10 + tmp[i];
    }
    memset(vis, 0, sizeof(vis));
    return 1;
}

int mask[] = {0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
inline
int get(int state, int ind) {
    state %= mask[ind+1];
    return state / mask[ind];
}
inline
void set(int &state, int ind, int val) {
    state -= mask[ind] * get(state, ind);
    state += val * mask[ind];
}

int rot(int state, int type) {
    int ret = state;
    if (type == 1) {
        set(ret, 1, get(state, 4));
        set(ret, 2, get(state, 3));
        set(ret, 3, get(state, 1));
        set(ret, 4, get(state, 2));
    } else if (type == 2) {
        set(ret, 1, get(state, 3));
        set(ret, 2, get(state, 4));
        set(ret, 3, get(state, 2));
        set(ret, 4, get(state, 1));
    } else if (type == 3) {
        set(ret, 1, get(state, 6));
        set(ret, 2, get(state, 5));
        set(ret, 5, get(state, 1));
        set(ret, 6, get(state, 2));
    } else if (type == 4) {
        set(ret, 1, get(state, 5));
        set(ret, 2, get(state, 6));
        set(ret, 5, get(state, 2));
        set(ret, 6, get(state, 1));
    }
    return ret;
}

void solve() {
    queue <int> q;
    queue <int> step;
    q.push(a);
    step.push(0);
    vis[a] = 1;
    while (not q.empty()) {
        int state = q.front(); q.pop();
        int st = step.front(); step.pop();
        //printf("%d %d\n", state, st);
        int r;
        for (int i = 1; i <= 4; ++ i) {
            r = rot(state, i);
            if (not vis[r]) {
                vis[r] = 1;
                q.push(r);
                step.push(st+1);
            }
        }
        if (state == b) {
            printf("%d\n", st);
            return;
        }
    }
    printf("-1\n");
}

int main() {
    while (input()) {
        solve();
    }
    return 0;
}
