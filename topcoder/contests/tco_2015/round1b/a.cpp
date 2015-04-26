#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

class TheNicePair {
  public:
    static const int maxn = 1010;
    int primes[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
    int n;
    int _sum[52];
    int *sum;

    int get(vector<int> a, int p) {
      int ans = 0;
      for (int i = 0; i < n; ++ i) {
        if (a[i]%p==0) {
          sum[i] = sum[i-1]+1;
        } else {
          sum[i] = sum[i-1];
        }
      }

      for (int i = 0; i < n; ++ i) {
        for (int j = 1; j < n; ++ j) {
          int cnt = (j-i+1);
          if ( sum[j]-sum[i-1] >= (cnt+1)/2 && cnt > ans) {
            ans = cnt-1;
          }
        }
      }


      return ans;
    }

    int solve(vector <int> a) {
      int ans = 0;
      n = (int) a.size();
      sum = _sum+1;
      sum[-1] = 0;

      int ac = 0;
      for (int i = 0; i < n; ++ i) {
        ac += a[i];
      }
      if (ac == n) return -1;

      for (int i = 0; i < 168; ++ i) {
        int tmp = get(a, primes[i]);
        if (tmp > ans) ans = tmp;
      }

      return ans;
    }
};

int main() {
  vector<int> a = {8,8,5,5,5};
  TheNicePair *t = new TheNicePair();
  printf("%d\n", t->solve(a) );

  return 0;
}
