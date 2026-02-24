#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
bool mem1;
namespace OIMATT{
	const int maxn=6e5+10;
	int n,m;
	pii a[maxn];
	void matt(){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)	scanf("%d",&a[i].fi),a[i].se=0;
		for(int i=1;i<=m;i++)	scanf("%d",&a[i+n].fi),a[i+n].se=1;
		sort(a+1,a+n+m+1);
		int r=0,c=0;ll ans=0,edg=0;
		for(int i=1;i<=n+m;i++){
			if(!a[i].se){
				int add=m-1;
				if(r)	add-=max(0,c-1);
				edg+=add;
				ans+=1ll*add*a[i].fi;
				r++;
			}
			else{
				int add=n-1;
				if(c)	add-=max(0,r-1);
				edg+=add;
				ans+=1ll*add*a[i].fi;
				c++;
			}
			// printf("%d %d %d %d %lld\n",a[i].fi,r,c,ans,edg);
		}
		printf("%lld\n",ans);assert(edg==1ll*n*m-1);
	}
}
bool mem2;
int main(){
	debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
	double sta=clock();
	int T=1;while(T--)OIMATT::matt();
	debug("%.0fms\n",(clock()-sta)/CLOCKS_PER_SEC*1000);
}