
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double x[50001];
int p[50001];
int n;
double max, min;

double f(double X) {
    double res = 0;
    for (int i = 0; i < n; ++ i) {
        res += (double)p[i] * abs(x[i] - X);
    }
    return res;
}

void solve() {
    double left = min;
    double right = max;
    double mid = (right - left) / 3.0 + left;
    double midmid = right - (right - left) / 3.0;
    double mid_f ;
    double midmid_f ;
    while (right - left > 0.000005) {
        mid_f = f(mid);
        midmid_f = f(midmid);
        printf("%lf %lf:%lf %lf\n", mid, midmid, mid_f, midmid_f);
        if (mid_f <= midmid_f) {
            right = midmid;
        }
        else {
            left = mid;
        }
        mid = (right - left) / 3.0 + left;
        midmid = right - (right - left) / 3.0;
    }
    printf("%.5lf\n", mid);
}

int main() {
    scanf("%d", &n);
    min = 10000000005;
    max  = 0;
    for (int i = 0; i < n; ++ i) {
        scanf("%lf %d", &x[i], &p[i]);
        min = min < x[i] ? min : x[i];
        max = max > x[i] ? max : x[i];
    }
    printf("%lf\n", f(2.5));
    return 0;
    solve();

    return 0;
}

