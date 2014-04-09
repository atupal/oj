
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int X[10];
int Y[10];
int v[10];
int e[10];
int a[10];
double min;
int n;
int head;
int H = 0;

void get(int i, double d) {
    int cnt = 0;
    for (int s = 0; s < n; ++ s) cnt += v[s];
    if (cnt == n){ 
        if (min > d){
            memcpy(a,e, sizeof(a));
            H = head;
            min = d;
        }
        return;
    }
    if (cnt == 0) head = i;
    if (d >= min) return;
    for (int x = 0; x < n; ++ x) {
        if (!v[x]) {
            v[x] = 1;
            e[i] = x;
            get(x, d + sqrt((X[i] - X[x]) * (X[i] - X[x]) + (Y[i] - Y[x]) * (Y[i] - Y[x])));
            v[x] = 0;
        }
    }
}

int main () {
    int cnt = 0;
    for(;;) {
        ++ cnt;
        min = 1e20;
        scanf("%d", &n);
        if (!n) return 0;
        memset(v, 0, sizeof(v));
        for (int i = 0; i < n; ++ i) scanf("%d %d", &X[i], &Y[i]);
        for (int i = 0; i < n; ++ i) get(i, 0.0);
        printf("**********************************************************\n");
        printf("Network #%d\n", cnt);
        int x,y;
        for (int i = 0, x = H, y = a[x]; i < n - 1; ++ i, x = y, y = a[x]) {
            double xxx = sqrt((X[x] - X[y]) * (X[x] -X[y]) + (Y[x] - Y[y]) * (Y[x] - Y[y]));
            printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n", X[x], Y[x], X[y], Y[y], xxx + 16);
        }
        printf("Number of feet of cable required is %.2f.\n", min + 16 * (n - 1));
    }
    return 0;
}

