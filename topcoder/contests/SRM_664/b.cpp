#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <queue>

using namespace std;

class BearPlaysDiv2 {
  public:

    int sum;

    int poll(int x, int type) {
      int A = x/1000;
      int B = x%1000;
      int C = sum-(A+B);
      if (type == 1) {
        if (A > B) {
          return (A-B)*1000+B*2;
        } else if (A < B) {
          return A*2*1000+B-A;
        }
      } else if (type == 2) {
        if (A > C) {
          return (A-C)*1000+B;
        } else if (A < C) {
          return A*2*1000+B;
        }
      } else if (type == 3) {
        if (B > C) {
          return A*1000+B-C;
        } else if (B < C) {
          return A*1000+B*2;
        }
      }

      return x;
    }

    string equalPiles(int A, int B, int C) {
      sum = A + B + C;
      queue<int> q;
      int vis[1000000];
      memset(vis, 0, sizeof(vis));
      q.push(A*1000+B);
      vis[A*1000+B]=1;
      while (!q.empty()) {
        int x = q.front(); q.pop();
        if ((x/1000) == (x%1000) && x/1000 == (sum-x/1000-(x%1000)) ) return "possible";
        for (int i = 1; i < 4; ++ i) {
          int n = poll(x, i);
          if (!vis[n]) {
            q.push(n);
            vis[n]=1;
          }
        }
      }

      return "impossible";
    }
};

int main() {
  BearPlaysDiv2 *b = new BearPlaysDiv2();
  printf("%s", b->equalPiles(1, 1, 2).c_str());

  return 0;
}

