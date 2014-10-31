/*
   将容斥原理变成乘法
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long exp(long long m,long long n) {
	long long ret = 1;
	while(n){
		if (n&1) ret *= m;
		m *= m;
		n>>=1;
	}
	return ret;
}

long long solve(long long n,long long m) {
	long long f = exp(m,n);
	long long x = m;
	for(long long i=2;i*i <= x; ++ i){
		if(m%i == 0){
			long long q = exp(i,n);
      //f = f - f/q
			f = f/q*(q-1);
			while(m%i == 0) m/=i;
		}
	}
	if(m>1) {
    long long q = exp(m, n);
    f = f/q*(q-1);
  }

	return f;
}
int main(){
	long long n,m;
	while (scanf("%lld%lld",&n,&m) != EOF)
		printf("%lld\n", solve(n,m));

	return 0;
}

