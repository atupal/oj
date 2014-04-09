
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <vector>
#define abs(x) (x) > 0 ? (x) : (-(x))
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

using namespace std;

queue<int> q;

const int maxn = 201;

int d;
int A, B, C;
int v[(1 << 25) + 100];

void pure(int f, int t, int &nf, int &nt, int cf, int ct) {
    int need = ct - t;
    nf = max(f - need, 0);
    nt = min(t + f, ct);
}

void bfs() {
    int Min = maxn * 200;
    int min = Min;
    int e;
    int ans = 0x7ffffff;
    int ans_2 = ans;
    while (!q.empty()) {
        e = q.front();
        q.pop();
        int a = (e >> 16);
        int b = (e >> 8) & ((1 << 8) - 1);
        int c = e & ((1 << 8) - 1);
        //printf("%d %d %d\n", a, b, c);
        if (a <= d && d - a < Min) {Min = d - a;}
        if (b <= d && d - b < Min) {Min = d - b;}
        if (c <= d && d - c < Min) {Min = d - c;}
        if (Min == 0) {
            ans = ans < v[e] ? ans : v[e];
        }
        else if (Min < min) {
            min = Min;
            ans_2 = ans_2 < v[e] ? ans_2 : v[e];
        }
        int na, nb, nc, t;
        int tmp;

        nc = c; pure(a, b, na, nb, A, B);
        tmp = v[e] + min(B - b, a);t = (na << 16) | (nb << 8) | nc; if (v[t] == -1)  {q.push(t);  v[t] = tmp;} else {v[t] = v[t] < tmp ? v[t] : tmp;}
                                                                                                     
        nc = c; pure(b, a, nb, na, B, A);                                      
        tmp = v[e] + min(A - a, b);t = (na << 16) | (nb << 8) | nc; if (v[t] == -1)  {q.push(t);  v[t] = tmp;} else {v[t] = v[t] < tmp ? v[t] : tmp;}
                                                                                                     
        nb = b; pure(a, c, na, nc, A, C);                                      
        tmp = v[e] + min(C - c, a);t = (na << 16) | (nb << 8) | nc; if (v[t] == -1)  {q.push(t);  v[t] = tmp;} else {v[t] = v[t] < tmp ? v[t] : tmp;}
                                                                                                     
        nb = b; pure(c, a, nc, na, C, A);                                      
        tmp = v[e] + min(A - a, c);t = (na << 16) | (nb << 8) | nc; if (v[t] == -1)  {q.push(t);  v[t] = tmp;} else {v[t] = v[t] < tmp ? v[t] : tmp;}
                                                                                                     
        na = a; pure(b, c, nb, nc, B, C);                                      
        tmp = v[e] + min(C - c, b);t = (na << 16) | (nb << 8) | nc; if (v[t] == -1)  {q.push(t);  v[t] = tmp;} else {v[t] = v[t] < tmp ? v[t] : tmp;}
                                                                                                     
        na = a; pure(c, b, nc, nb, C, B);                                      
        tmp = v[e] + min(B - b, c);t = (na << 16) | (nb << 8) | nc; if (v[t] == -1)  {q.push(t);  v[t] = tmp;} else {v[t] = v[t] < tmp ? v[t] : tmp;}

    }
    if (not Min)
        printf("%d %d\n", ans, d);
    else
        printf("%d %d\n", ans_2, d - Min);
}



int main() {
    int tn;
    scanf("%d", &tn);
    while (tn --) {
        scanf("%d%d%d%d", &A, &B, &C, &d);
        memset(v, -1, sizeof(v));
        v[C] = 0;
        q.push(C);
        bfs();
    }

    return 0;
}

