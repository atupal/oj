#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const double PI=acos(-1.0);

double angle(double x1, double y1, double x2, double y2) {
  double a=0,b=0;
  a=atan2(y1,x1);
  b=atan2(y2,x2);
  return fmod(  (a-b)+5*PI  , 2*PI)  - PI;
}

int main() {
  double max = 0 ,min = 0;
  double k, h;
  int n;
  scanf("%lf %lf %d", &k, &h, &n);
  double x0,y0;
  scanf("%lf %lf", &x0, &y0);
  double x1=x0,y1=y0;
  double ret=0;
  double x, y;
  while (--n) {
    scanf("%lf %lf", &x, &y);
    ret += angle(x1, y1, x, y);
    max=ret>max?ret:max;
    min=ret<min?ret:min;
    x1=x;y1=y;
  }
  ret += angle(x, y, x0,y0);
  max=ret>max?ret:max;
  min=ret<min?ret:min;
  if(max-min>2*PI){max=2*PI;min=0;}

  //printf("%.2lf", (max-min) * k * h);
  //妈蛋这里改成lf是过不了的。要f..
  printf("%.2f", (max-min) * k * h);
  return 0;
}
