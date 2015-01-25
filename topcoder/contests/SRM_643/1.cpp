#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

class TheKingsArmyDiv2 {
  public:
  int getNumber(vector <string> state) {
    int r = state.size();
    int c = strlen(state[0].c_str());
    int flag = 0;
    int x[] = {1, -1, 0, 0};
    int y[] = {0, 0, 1, -1};
    for (int i = 0; i < r; ++ i) {
      for (int j = 0; j < c; ++ j) {
        if (state[i][j] == 'H') {
          flag = 1;
          for (int k = 0; k < 4; ++ k) {
            int xx = i+x[k];
            int yy = j+y[k];
            if (xx >= 0 && xx < r && yy >= 0 && yy < c && state[xx][yy] == 'H') {
              return 0;
            }
          }
        }
      }
    }
    if (flag) return 1;
    return 2;
  }
};

int main() {
  return 0;
}
