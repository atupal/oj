#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int xa, ya, xb, yb, xc, yc;
int d, v;

double ta, tb, tc;
double ab, bc, ac;
#define sq(x) (x)*(x)

int main() {
  scanf("%d %d %d %d %d %d", &xa, &ya, &xb, &yb, &xc, &yc);
  ab = sqrt((double)sq(xa-xb) + (double)sq(ya-yb));
  bc = sqrt((double)sq(xc-xb) + (double)sq(yc-yb));
  ac = sqrt((double)sq(xa-xc) + (double)sq(ya-yc));
  scanf("%d %d", &d, &v);
  ta = d+60.*(ac+bc)/v*1.;
  int th, tm, fh, fm;
  scanf("%d:%d %d:%d",&th, &tm, &fh, &fm);
  tb = (th-9)*60+tm + fh*60 + fm;
  int w;
  scanf("%d", &w);
  tc = (ab)/(double) w * 60.;
  if ( (yb-ya)*(xc-xa) == (xb-xa)*(yc-ya)) 
    tc += d;

  //if (ac+bc==ab) tc += d;
  //printf("%lf %lf %lf\n", ta, tb, tc);
  if (ta < tb && ta < tc) {
    printf("Alex\n");
  } else if (tb < ta && tb < tc) {
    printf("Dmitry\n");
  } else {
    printf("Petr\n");
  }


  return 0;
}
