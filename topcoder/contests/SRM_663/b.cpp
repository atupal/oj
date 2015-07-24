#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

class ABBA {
  public:
    string canObtain(string initial, string target) {
      int b[1002];
      b[0] = 0;

      int l1 = initial.size();
      int l2 = target.size();

      for (int i = 0; i < l2; ++ i) {
        b[i+1] = b[i];
        if (target[i] == 'B') {
          b[i+1]++;
        }
      }

      if (l1 > l2) return "Impossible";

      for (int i = 0; i <= l2-l1; ++ i) {
        int flag = 1;
        for (int j = 0; j < l1; ++ j) {
          if (initial[j] != target[j+i]) {
            flag = 0;
            break;
          }
        }
        if (flag) {
          if (b[i] == b[l2] - b[i+l1]) {
            return "Possible";
          }
        }

        flag = 1;
        for (int j = 0; j < l1; ++ j) {
          if (initial[l1-1-j] != target[j+i]) {
            flag = 0;
            break;
          }
        }
        if (flag) {
          if (b[l2] - b[i+l1] - b[i] == -1 || b[l2] - b[i+l1] - b[i] == 1) {
            return "Possible";
          }
        }

      }


      return "Impossible";
    }
};


int main() {
  ABBA *c = new ABBA();
  cout << c->canObtain("AB", "BAB");

  return 0;
}
