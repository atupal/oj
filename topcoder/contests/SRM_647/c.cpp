#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

typedef long long int64;

class BuildingTowers {
  public:

    int n;
    int k;

    int64 max(int64 a, int64 b) {
      return a > b ? a : b;
    }

    int64 min(int64 a, int64 b) {
      return a < b ? a : b;
    }

    int64 get(int64 h, int64 n) {

      if (n<=1) return min(k, h);

      int64 ret;
      int64 pos = (int64) (  ( (double)n*(double)k + (double)h ) / (2. * (double)k)  );
      ret = pos*k;
      if (pos+1 <= n) {
        ret = max(ret, (n-pos-1)*k+h);
      }

      return ret;
    }

    int64 maxHeight(int64 N, int64 K, vector <int> x, vector <int> t) {

      if ( x.empty() || (x.size() == 1 && x[0] == 1)) return (N-1)*K;

      if (x[0] != 1) {
        x.insert(x.begin(), 1);
        t.insert(t.begin(), 0);
      }
      k = K;

      int64 ans = 0;
      n = x.size();

      for (int i = 1; i < n; ++ i) {

        int64 low = 0;
        int64 high = t[i-1];
        while (low < high) {
          int64 mid = (1+low+high)>>1; 
          int64 h = mid;
          int flag = 1;
          for (int j = i-1; j>=0; -- j) {
            if ( h > t[j] ) {
              flag = 0;
              break;
            }
            if (j-1>=0) h = max(0, h - k*( x[j]-x[j-1] ));
          }
          if (!flag) {
            high = mid-1;
          } else {
            low = mid;
          }
        }
        int64 l = low;

        low = 0;
        high = t[i];
        while (low < high) {
          int64 mid = (low+high+1)>>1; 
          int64 h = mid;
          int flag = 1;
          for (int j = i; j<n; ++ j) {
            if ( h > t[j] ) {
              flag = 0;
              break;
            }
            if (j+1<n) h = max(0, h - k*( x[j+1]-x[j] ));
          }
          if (!flag) {
            high = mid-1;
          } else {
            low = mid;
          }
        }

        int64 r = low;

        ans = max(ans, min(l, r) + get(max(r, l) - min(l, r), x[i]-x[i-1]));
      }

      int64 low = 0;
      int64 high = t[n-1];
      while (low < high) {
        int64 mid = (1+low+high)>>1; 
        int64 h = mid;
        int flag = 1;
        for (int j = n-1; j>=0; -- j) {
          if ( h > t[j] ) {
            flag = 0;
            break;
          }
          if (j-1>=0) h = max(0, h - k*( x[j]-x[j-1] ));
        }
        if (!flag) {
          high = mid-1;
        } else {
          low = mid;
        }
      }
      ans = max(ans, (N-x[n-1])*k+low);

      return ans;
    }

};

int main() {
  printf("%d\n", (int)1.99);  // is 1

  return 0;
}
