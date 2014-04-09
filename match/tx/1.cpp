
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int maxn = 101;
int n;
long double k1,k2,k;
long double A[10010];

struct num{
    int d[maxn];
    int point;
    num() {
        memset(d, 0, sizeof(int) * maxn);
        point = 0;
    }
};

int max(int a, int b) {
    return a > b ? a : b;
}

num mul(num a, num b) {
    num c;
    memset(c.d, 0, sizeof(int) * maxn);
    for (int i = 0; i < maxn; ++ i) {
        for (int j = 0; j < maxn; ++ j) {
            if (i + j < maxn)
            c.d[i + j] += a.d[i] * b.d[j];
        }
    }
    for (int i = 0; i < maxn; ++ i) {
        c.d[i + 1] += c.d[i] / 10;
        c.d[i] %= 10;
    }
    c.point = a.point * b.point;
    int t = 0;
    while(!c.d[t] && t < c.point) 
        ++ t;
    c.point -= t;
    for (int i = 0; i < maxn- t; ++ i) {
        c.d[i] = c.d[i + t];
    }
    for (int i = 0; i < maxn; ++ i) {
        a.d[i]=  c.d[i];
    }
    a.point = c.point;
    return c;
}

int get(num a) {

}

void solve(int index, num sum) {
    double t = k1 + k2;
    if(t <= 1 && t >= -1){
        if (sum * t > k) {
            printf("Case of #%d: 1\n", index);
        }
        else 
            printf("Case of #%d: inf\n", index);
    }
    else {
        int cnt = 0;
        while (!get()) {
            cnt += 1;
            mul(sum, sum);
        }
        printf("Case of #%d: %d\n",index, cnt);
    }
}


int main() {
    int t;
    scanf("%d", &t);
    int T = t;
    while (t --) {
        long double sum = 0;
        scanf("%d %Lf %Lf %Lf", &n, &k1, &k2, &k);
        for (int i = 0; i < n; ++ i) {
            scanf("%Lf", &A[i]);
            sum += A[i];
        }
        num a ;
        int t = 0;
        for (sum) {
            a.d[t] = sum % 10;
            sum /= 10;
        }
        if (sum > k) printf("Case #%d: 0\n", T-t);
        else
        solve(T - t,a);
    }

    return 0;
}

