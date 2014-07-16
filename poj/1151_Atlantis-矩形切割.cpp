/*
http://blog.csdn.net/sdj222555/article/details/7234970
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
int n;
double xa[1010], xb[1010], ya[1010], yb[1010], area;
void cover(double lx, double rx, double ly, double ry, int t) {
    while((t <= n) && ((lx >= xb[t]) || (rx <= xa[t]) || (ly >= yb[t]) || (ry <= ya[t])))
        t++;
    if(t > n) {
        area += (rx - lx ) * (ry - ly);
        return;
    }
    if(lx < xa[t]) {
        cover(lx, xa[t], ly, ry, t + 1 );
        lx = xa[t];
    }
    if(rx > xb[t]) {
        cover(xb[t], rx , ly, ry, t + 1 );
        rx = xb[t];
    }
    if(ly < ya[t]) {
        cover(lx, rx, ly, ya[t], t + 1 );
        ly = ya[t];
    }
    if(ry > yb[t]) {
        cover(lx, rx, yb[t], ry, t + 1 );
        ry = yb[t];
    }
}

int main() {
    int cas = 0;
    while(scanf("%d", &n) != EOF && n) {
        area = 0;
        for(int i = 1; i <= n; i++)
            scanf("%lf%lf%lf%lf", &xa[i], &ya[i], &xb[i], &yb[i]);
        for(int i = n; i >= 1; i--)
          cover(xa[i], xb[i], ya[i], yb[i], i + 1);
        printf("Test case #%d\n", ++cas);
        printf("Total explored area: %.2f\n\n", area);
    }
    return 0;
}
