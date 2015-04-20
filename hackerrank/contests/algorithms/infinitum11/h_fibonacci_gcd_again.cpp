#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

typedef long long ll;
ll N, MOD;
ll a[3];
ll b[3];
ll n;

ll fibs[] = {0, 1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903,2971215073,4807526976,7778742049,12586269025};

ll fib(ll, ll);
long long getFib(long long n,int m);

ll gcd(ll a, ll b) {
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  return b == 0 ? a : gcd(b, a%b);
}

double ABS(double a) {
  return a < 0 ? -a : a;
}

double get_fib_coefficient(ll *a) {
  return (double) a[0] + (double) a[1] * (double)1.61803398875;
}

void solve_error() {
  if (N < 47) {
    ll A = a[0]*fibs[N] + a[1]*fibs[N+1] + a[2]*fibs[N+2];
    ll B = b[0]*fibs[N] + b[1]*fibs[N+1] + b[2]*fibs[N+2];
    printf("%lld\n", gcd(A, B)%MOD);
    return;
  }

  a[0] += a[2], a[1] += a[2];
  b[0] += b[2], b[1] += b[2];
  double A = 1.0, B = 0.0;
  double tmpA = -1, tmpB = -1;
  ll ans1, ans2;
  while (1) {
  //for (int i = 0; i < 100; ++ i) {
    A = get_fib_coefficient(a);
    B = get_fib_coefficient(b);
    if (ABS(tmpA - A) < 0.000001 && ABS(tmpB - B) < 0.000001) break;
    //printf("A, B -> %lf %lf\n", A, B);
    if (A > B) {
      int q = (int) A/B;
      a[0] -= q*b[0];
      a[1] -= q*b[1];
      //printf("%lld %lld\n", a[0], a[1]);
    } else {
      int q = (int)B/A;
      b[0] -= q*a[0];
      b[1] -= q*a[1];
      //printf("%lld %lld\n", b[0], b[1]);
    }
    tmpA = A;
    tmpB = B;

  }

  ans1 = ( (a[0]%MOD)*fib(N, MOD)%MOD + MOD) % MOD + ( a[1]%MOD*fib(N+1, MOD)%MOD + MOD) % MOD;
  ans1 %= MOD;

  ans2 = ( (b[0]%MOD)*fib(N, MOD)%MOD + MOD) % MOD + ( b[1]%MOD*fib(N+1, MOD)%MOD + MOD) % MOD;
  ans2 %= MOD;

  if (!ans1) ans1 = ans2;

  printf("%lld\n", ans1);
}

void solve() {
  a[0] += a[2]; a[1] += a[2];
  b[0] += b[2]; b[1] += b[2];
  // gcd(a0Fn + a1Fn+1, b0Fn + b1Fn+1) -> gcd(a0%b0Fn + a1%b1Fn+1, b0Fn + b1Fn+1) ->
  // ... ->
  // gcd(a0'Fn + a1'Fn+1, b0'Fx + 0*Fy)   x,y == n | n+1
  ll x = N;
  while (1) {
    if (a[0] == 0) {
      a[0] ^= b[0] ^= a[0] ^= b[0];
      a[1] ^= b[1] ^= b[1] ^= b[1];
      b[0] = b[1];
      x = N+1;
      break;
    }
    if (a[1] == 0) {
      a[0] ^= b[0] ^= a[0] ^= b[0];
      a[1] ^= b[1] ^= b[1] ^= b[1];
      break;
    }
    if (b[0] == 0) {
      b[0] = b[1];
      x = N+1;
      break;
    }
    if (b[1] == 0) {
      break;
    }
    a[0] %= b[0];
    a[1] %= b[1];
    a[0] ^= b[0] ^= a[0] ^= b[0];
    a[1] ^= b[1] ^= b[1] ^= b[1];
  }

  /*
   * gcd(a0'Fn + a1'Fn+1, b0'Fx)
   * gcd(a0'Fn + a1'Fn+1, xxx) = gcd( (a0'Fn+a1'Fn+1)%xxx,  xxx)
   * */

}

int main()
{
    int T,a,b,c,d,e,f,m;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%d%d%d%d%d%d%d",&n,&a,&b,&c,&d,&e,&f,&m);
        a+=c;
        b+=c;
        d+=f;
        e+=f;
        while(e)
        {
            f=b/e;
            b-=f*e;
            a-=f*d;
            swap(b,e);
            swap(a,d);
        }
        c=d>0?d:-d;
        if(c==0)
        {
            printf("%lld\n",(getFib(n,m)*a%m+getFib(n+1,m)*b%m+m)%m);
            continue;
        }
        if(b==0)
        {
            printf("%lld\n",getFib(n,m)*gcd(a,c)%m);
            continue;
        }
        c*=gcd(getFib(n,b),b);
        printf("%lld\n",gcd(a*getFib(n,c)+b*getFib(n+1,c),c)%m);
    }
    return 0;
}

int my_main() {
  int T;
  scanf("%d", &T);
  for (int i = 0 ; i < T; ++ i) {
    scanf("%lld %lld %lld %lld %lld %lld %lld %lld", &N, a, a+1, a+2, b, b+1, b+2, &MOD);
    solve();
  }

  return 0;
}

ll fib(ll n, ll MOD) {
  if (n == 0) return 0ll;
  ll a = 1, b = 1;
  ll A[2][2], ret[2][2], base[2][2], tmp[2][2];
  
  A[0][0] = 0;
  A[0][1] = 1;
  A[1][0] = 1;
  A[1][1] = 1;
  memcpy(ret, A, sizeof(A));
  memcpy(base, A, sizeof(A));
  if (n <= 2) {
    return 1ll;
  }
  n -= 2;
  while (n) {
    if (n&1) {
      tmp[0][0] = (ret[0][0] * base[0][0] % MOD + ret[0][1] * base[1][0] % MOD )%MOD;
      tmp[0][1] = (ret[0][0] * base[0][1] % MOD + ret[0][1] * base[1][1] % MOD )%MOD;
      tmp[1][0] = (ret[1][0] * base[0][0] % MOD + ret[1][1] * base[1][0] % MOD )%MOD;
      tmp[1][1] = (ret[1][0] * base[0][1] % MOD + ret[1][1] * base[1][1] % MOD )%MOD;
      memcpy(ret, tmp, sizeof(tmp));
    }
    tmp[0][0] = (base[0][0] * base[0][0] % MOD + base[0][1] * base[1][0] % MOD)%MOD;
    tmp[0][1] = (base[0][0] * base[0][1] % MOD + base[0][1] * base[1][1] % MOD)%MOD;
    tmp[1][0] = (base[1][0] * base[0][0] % MOD + base[1][1] * base[1][0] % MOD)%MOD;
    tmp[1][1] = (base[1][0] * base[0][1] % MOD + base[1][1] * base[1][1] % MOD)%MOD;
    memcpy(base, tmp, sizeof(tmp));
    n >>= 1ll;
  }
  ll ans = (ret[0][0] * a % MOD + ret[0][1] * b % MOD) % MOD;
  return ans;
}

ll gcdEx(ll a, ll b, ll *x, ll *y) {
  if(b==0) {
    *x = 1ll,*y = 0ll;
    return a;
  } else {
    ll r = gcdEx(b, a%b, x, y);
    ll t = *x;
    *x = *y;
    *y = t - a/b * *y;
    return r;
  }
}


long long getFib(long long n,int m)
{
    int a[2][2];
    int b[2][2];
    long long c[2][2];
    int i,j,k;
    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
        {
            a[i][j]=i|j;
            b[i][j]=i==j;
        }
    while(n)
    {
        if(n%2)
        {
            for(i=0;i<2;i++)
                for(j=0;j<2;j++)
                    c[i][j]=(long long)b[i][0]*a[0][j]+(long long)b[i][1]*a[1][j];
            for(i=0;i<2;i++)
                for(j=0;j<2;j++)
                    b[i][j]=c[i][j]%m;
        }
        for(i=0;i<2;i++)
            for(j=0;j<2;j++)
                c[i][j]=(long long)a[i][0]*a[0][j]+(long long)a[i][1]*a[1][j];
        for(i=0;i<2;i++)
            for(j=0;j<2;j++)
                a[i][j]=c[i][j]%m;
        n/=2;
    }
    return b[0][1];
}
