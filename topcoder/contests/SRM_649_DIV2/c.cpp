#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

class XorSequenceEasy {
  public:
    int ds;
    int ans;

    int getmax(vector <int> A, int N) {
      ans = 0;
      ds = 0;
      while (N) {
        ds += 1;
        N >>= 1;
      }
      int r[51][51];
      memset(r, 0, sizeof(r));
      int n = (int) A.size();
      for (int pos = ds-2; pos>=0; -- pos) {
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < n; ++ i) {
          for (int j = i+1; j < n; ++ j) {
            if (!r[i][j]) {
              if ( (A[i]&(1<<pos)) < (A[j]&(1<<pos)) ) {
                cnt1 += 1;
              }
            }
          }
        }

        for (int i = 0; i < n; ++ i) {
          for (int j = i+1; j < n; ++ j) {
            if (!r[i][j]) {
              if ( (A[i]&(1<<pos)) > (A[j]&(1<<pos)) ) {
                cnt2 += 1;
              }
            }
          }
        }

        if (cnt1 > cnt2) {
          ans += cnt1;
        } else {
          ans += cnt2;
        }

        for (int i = 0; i < n; ++ i) {
          for (int j = i+1; j < n; ++ j) {
            if ( (A[i]&(1<<pos)) != (A[j]&(1<<pos)) ) {
              r[i][j] = 1;
            }
          }
        }


      }


      return ans;
    }
};

int main() {
  vector<int> A = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9};
  int n = 16;
  //vector<int> A = {3,0,4,6,1,5,7,6};
  //int n = 8;
  XorSequenceEasy x;
  printf("%d\n", x.getmax(A, n));

  return 0;
}
