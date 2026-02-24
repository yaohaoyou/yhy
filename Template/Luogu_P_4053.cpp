//  P4053 [JSOI2007] 建筑抢修/反悔贪心
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
struct node {
	long long t1,t2;
	friend bool operator < (const node &a,const node &b) {
		return a.t2 < b.t2;
	}
} a[1000005];
priority_queue<long long> q;
long long n,sum=0,ans=0;
int main() {
	cin>>n;
	for (int i=1; i<=n; i++) {
		scanf("%lld%lld",&a[i].t1,&a[i].t2);
	}
	sort(a+1,a+n+1);
	for(int i=1; i<=n; i++) {
		sum+=a[i].t1;
		ans++;
		q.push(a[i].t1);
		if(a[i].t2<sum) {
			sum-=q.top();
			ans--;
			q.pop();
		}
	}
	printf("%lld",ans);
}