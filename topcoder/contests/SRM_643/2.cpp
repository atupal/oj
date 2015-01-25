#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

typedef long long int64;
typedef unsigned long long uint64;

class TheKingsFactorization {
  public:
  vector<int64> getVector(int64 N, vector<int64> primes) {
    vector <int64> ans;
    int m = primes.size();
    if (m == 1) {
      ans.push_back(primes[0]);
      if (primes[0] != N) {
        ans.push_back(N/primes[0]);
      }
      return ans;
    }

    for (int64 x = primes[0]; x <= primes[m-2]; ++ x) {
      while (N%x == 0) {
        ans.push_back(x);
        N /= x;
      }
    }
    if (N==1) return ans;

    if (primes[m-1] == primes[m-2]) {
      ans.push_back(N);
      return ans;
    }

    if (primes[m-1]*primes[m-1] == N) {
      ans.push_back(primes[m-1]);
      ans.push_back(primes[m-1]);
      return ans;
    }

    if (N%(primes[m-1]*primes[m-1]) == 0) {
      ans.push_back(primes[m-1]);
      ans.push_back(primes[m-1]);
      ans.push_back(N/primes[m-1]/primes[m-1]);
      return ans;
    }

    if (N == primes[m-1]) {
      ans.push_back(primes[m-1]);
      return ans;
    }

    int64 rest = N/primes[m-1];
    if (rest <= primes[m-1]) {
      ans.push_back(rest);
      ans.push_back(primes[m-1]);
      return ans;
    }

    int64 b = rest/primes[m-1];
    if (primes[m-1]<b) b=primes[m-1];
    for (int64 x = primes[m-2]; x <= b; ++ x) {
      if (rest%x == 0) {
        ans.push_back(x);
        ans.push_back(primes[m-1]);
        ans.push_back(rest/x);
        return ans;
      }
    }

    ans.push_back(primes[m-1]);
    ans.push_back(rest);
    return ans;
  }
};

int main() {
  return 0;
}
