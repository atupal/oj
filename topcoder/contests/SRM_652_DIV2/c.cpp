#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include <string.h>

using namespace std;

class NoRightTurnDiv2 {
  public:
    int vis[100];

    int cross(int x1, int y1, int x2, int y2, int x3, int y3) {
      int v1_x = (x2-x1);
      int v1_y = (y2-y1);
      int v2_x = (x3-x2);
      int v2_y = (y3-y2);
      int ret = v1_x*v2_y - v1_y*v2_x;
      return ret > 0;
    }

    vector <int> findPath(vector <int> x, vector <int> y) {
      vector<int> ret;
      memset(vis, 0, sizeof(vis));
      int n = (int) x.size();
      int now = 0;
      for (int i = 1; i < n; ++ i) {
        if (make_pair(x[i], y[i]) < make_pair(x[now], y[now])) {
          now = i;
        }
      }

      vis[now] = 1;
      ret.push_back(now);

      /*
         类似找 凸包

         暴力：先找出最左下点作为起始点，然后枚举下一个点，使得没有在 结果集 中的所有的点都在当前点
         和枚举的点组成的线段的左边(叉积)。
       */
      for (int i = 0; i < n-1; ++ i) {
        for (int j = 0; j < n; ++ j) if (!vis[j]) {
          int flag = 1;
          for (int k = 0; k < n; ++ k) if (!vis[k] && j != k) {
            if (!cross(x[now], y[now], x[j], y[j], x[k], y[k])) {
              flag = 0;
              break;
            }
          }
          if (flag) {
            now = j;
            vis[j] = 1;
            ret.push_back(now);
            break;
          }
        }
      }

      return ret;
    }

};

int main() {
  vector<int> x= {-76,98,83,58,-15,94,21,55,80,84,-39,-90,-46,100,-80,-49,-2,-70,36,48,88,10,
    55,-56,22,67,31,81,100,-39,64,-62,-7,45,-82,-24,51,-33,53,11,20,-74,-83,47,
    9,39,42,63,-97,94};
  vector<int> y = {-90,68,91,-92,-6,88,99,10,39,-69,-61,-4,71,-5,90,-51,21,-53,-21,-86,41,-9,
    42,-23,-4,12,94,-59,55,18,70,-88,-86,-17,-97,-33,87,80,91,-80,-79,-79,-78,
    -99,57,67,-52,-46,61,-10};

  NoRightTurnDiv2 t = NoRightTurnDiv2();
  vector<int> ret = t.findPath(x, y);
  for (int i = 0; i < (int)x.size(); ++ i) {
    printf("%d ", ret[i]);
  }

  return 0;
}
