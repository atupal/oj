#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
 
inline
int mod(int a,int b,int m){
    int result = 1;
    int base = a;
    while(b>0){
        if((b&1)==1){
            result = (result*base) % m;
        }
        base = (base*base) %m;
        b >>= 1;
    }
    return result;
}

void input() {
}

void solve() {
}

int main() {
    input();
    solve();
    return 0;
}

