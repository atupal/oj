/*
ID: sdj22251
PROG: rect1
LANG: C++
*/
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#define MAXN 2555
#define MAXM 104444
#define INF 100000000
#define eps 1e-7
#define L(X) X<<1
#define R(X) X<<1|1
using namespace std;
int n;
double xa[1010], xb[1010], ya[1010], yb[1010], area;
void cover(double lx, double rx, double ly, double ry, int t)
{
    while((t <= n) && ((lx >= xb[t]) || (rx <= xa[t]) || (ly >= yb[t]) || (ry <= ya[t])))
        t++;
    if(t > n)
    {
        area += (rx - lx ) * (ry - ly);
        return;
    }
    if(lx < xa[t])
    {
        cover(lx, xa[t], ly, ry, t + 1 );
        lx = xa[t];
    }
    if(rx > xb[t])
    {
        cover(xb[t], rx , ly, ry, t + 1 );
        rx = xb[t];
    }
    if(ly < ya[t])
    {
        cover(lx, rx, ly, ya[t], t + 1 );
        ly = ya[t];
    }
    if(ry > yb[t])
    {
        cover(lx, rx, yb[t], ry, t + 1 );
        ry = yb[t];
    }
}
int main()
{
    int cas = 0;
    while(scanf("%d", &n) != EOF && n)
    {
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

