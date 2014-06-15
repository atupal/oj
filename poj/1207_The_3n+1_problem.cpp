#include<stdio.h>
#include<string.h>
#define maxn 100000

#define max(a, b) (a) > (b) ? (a) : (b)

struct node {
	long long left;
	long long right;
	long long max;
};
long long dp[maxn+5];
node tree[3*maxn];

void dfs(long long n,long long num,long long id) {
	if(n<maxn && dp[n]!=-1) {
		dp[id]=dp[n]+num;
		return;
	} else {
		if(n&1) {
			n=n*3+1;
			dfs(n,num+1,id);
		} else {
			n=n/2;
			dfs(n,num+1,id);
		}
	}
}

void build(long long left,long long right,long long root) {
	tree[root].left=left;
	tree[root].right=right;
	if(left==right) {
		tree[root].max=dp[left];
		return;
	}
	long long mid=(left+right)>>1;
	build(left,mid,root*2);
	build(mid+1,right,root*2+1);
	tree[root].max=max(tree[2*root].max,tree[2*root+1].max);
}

void init() {
	long long i;
	memset(dp,-1,sizeof(dp));
	dp[1]=1;
	for(i=1;i<=maxn;i++)
		dfs(i,0,i);
	build(1,maxn,1);
}

long long search(long long left,long long right,long long root) {
	if(tree[root].left==left&&tree[root].right==right)
		return tree[root].max;
	long long mid=(tree[root].left+tree[root].right)>>1;
	if(right<=mid)
		return search(left,right,root*2);
	else if(left>mid)
		return search(left,right,root*2+1);
	else
		return max(search(left,mid,root*2),search(mid+1,right,root*2+1));
}

int main() {
	init();
	long long a,b;
	while (scanf("%lld%lld",&a,&b)!=EOF) {
    printf("%lld %lld ", a, b);
		if(a>b) a ^= b ^= a ^= b;
		printf("%lld\n", search(a,b,1));
	}

	return 0;
}
