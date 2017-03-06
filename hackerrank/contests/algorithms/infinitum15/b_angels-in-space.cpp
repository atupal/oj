#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int maxn = 109;

struct vector {
  int x,y,z;
};

double dot(vector a, vector b) {
  double ret;
  ret = a.x*b.x + a.y*b.y + a.z*b.z;

  return ret;
}

double length(vector a) {
  double qsum = a.x*a.x + a.y*a.y + a.z*a.z;
  return sqrt(qsum);
}

double angel(vector a, vector b) {
  double cosval = dot(a, b)/(length(a)*length(b));

  return acos(cosval);
}

double angel_3_points(vector a, vector b, vector c) {
  vector ba = {.x = a.x-b.x, .y = a.y-b.y, .z= a.z-b.z};
  vector bc = {.x = c.x-b.x, .y = c.y-b.y, .z= c.z-b.z};

  return angel(ba, bc);
}

int n;
vector points[maxn];
vector  current[3];
double sum = 0;
int cnt = 0;

void pick(int idx, int from) {
  if (idx == 3) {
    sum += angel_3_points(current[0], current[1], current[2]);
    cnt ++;
    return;
  }
  if (from >= n) return;
  current[idx] = points[from];
  pick(idx+1, from+1);
  pick(idx, from+1);
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%d %d %d", &points[i].x, &points[i].y, &points[i].z);
  }

  pick(0, 0);

  printf("%.12lf\n", sum/(double)cnt);

  return 0;
}

