#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

const int maxn = 50001;
int n;
double x[maxn];
double y[maxn];

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


double f(double X) {
    double sum = 0.0;
    for (int i = 0; i < n; ++ i) {
        double tmp = dist(X, 0.0, x[i], y[i]);
        sum = tmp > sum ? tmp : sum;
    }
    return sum;
}

void solve() {
    double l = -10000.0;
    double r = 10000.0;
    double mid;
    double midmid;
    while (r - l > 0.0000005) {
        mid = l + (r - l) / 3.0;
        midmid = r - (r - l) / 3.0;
        double mid_f = f(mid);
        double midmid_f = f(midmid);
        if (mid_f < midmid_f) {
            r = midmid;
        }
        else{
            l = mid;
        }
    }
    printf("%.6lf\n", mid);
}


int main() {
    int T;
    scanf("%d", &T);
    for (int c = 1; c <= T; ++ c) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            scanf("%lf %lf", &x[i], &y[i]);
        }
        printf("Case #%d: ", c);
        solve();
    }

    return 0;
}
