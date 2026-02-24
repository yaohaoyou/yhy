//  P5656 【模板】二元一次不定方程 (exgcd)
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
int gcd(int a,int b) {
	if(b==0) return a;
	return gcd(b,a%b);
}
ll exgcd(ll a,ll b,ll &x,ll &y) {
	ll m=a;
	if(b==0) {
		x=1,y=0;
		return m;
	} else m=exgcd(b,a%b,y,x),y-=a/b*x;
	return m;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll T,a,b,c,x0,y0,x,y;
	cin>>T;
	while(T--) {
		cin>>a>>b>>c;
		ll x,y,minx,maxx,miny,maxy,d=gcd(a,b),l;
		// ax+by=d
		if(c%d!=0) {
			puts("-1");
			continue;
		}
		a/=d,b/=d,c/=d;
		exgcd(a,b,x,y);
		x*=c,y*=c;
//		printf("a=%d b=%d c=%d d=%d x=%d y=%d\n",a,b,c,d,x,y);
		// a*x*c+b*y*c=c;
		minx=x%b+b,maxy=(c-a*minx)/b;
		miny=y%a+a,maxx=(c-b*miny)/a;
		if(x<=0) {
			ll l=-x/b+1;
			x=x%b+b;
			y=y-l*a;
			if(y<=0) {
				printf("%d %d\n",x,y%a+a);
				continue;
			}
		}
		if(y<=0) {
			ll l=-y/a+1;
			y=y%a+a;
			x=x-l*b;
			if(x<=0) {
				printf("%d %d\n",x%b+b,y);
				continue;
			}
		}
		l=x/b;
		x%=b;
		if(x==0) {
			x+=b;
			l--;
		}
		y+=l*a;
		ll minx1=x,maxy1=y;
		l=y/a;
		y%=a;
		if(y==0) {
			y+=a;
			l--;
		}
		x+=l*b;
		ll maxx1=x,miny1=y;
		printf("%d %d %d %d %d\n",(maxx1-minx1)/b+1,minx1,miny1,maxx1,maxy1);
	}
	return 0;
}