/*
   题意: n 个圆，互不相交，只有包含或者不包含关系，找出所有没有被其他圆包含的圆

   算法：扫描线，沿 x 轴扫描，直径左端点就加入队列，并判断 y 轴上下最近的两个圆心是否包含，否则不加入
                                  右端点如果圆在队列中就去掉圆.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

const int maxn = 4e4+10;
int n;
double r[maxn];
double x[maxn];
double y[maxn];
vector<int> ans;
pair<double, int> event[maxn<<1];
set<pair<double, int> > open;
set<pair<double, int> >::iterator it;

int inside(int a, int b) {
  return (x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]) <= r[b]*r[b];
}

void solve() {
  for (int i = 0; i < n; ++ i) {
    event[i<<1] = make_pair(x[i]-r[i], i);
    event[i<<1|1] = make_pair(x[i]+r[i], i+n);
  }
  int b = n<<1;
  sort(event, event+b);
  for (int i = 0; i < b; ++ i) {
    int id = event[i].second % n;
    if ( event[i].second < n) {
      it = open.lower_bound(make_pair(y[id], id));
      if ((it != open.end() && inside( id, it->second )) || 
          (it != open.begin() && inside( id, (--it)->second )) ) continue;
      open.insert(make_pair(y[id], id));
      ans.push_back(id+1);
    } else {
      open.erase(make_pair( y[id], id));
    }
  }
  sort(ans.begin(), ans.end());
  printf("%d\n", (int)ans.size());
  for (int i = 0; i < (int)ans.size(); ++ i) printf("%d ", ans[i]);
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    scanf("%lf %lf %lf", r+i, x+i, y+i);
  }
  solve();

  return 0;
}
