#pragma GCC optimize(2,3,"Ofast")
#include<bits/stdc++.h>
#define db double
#define ll long long
#define ep emplace
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
const int mod=998244353;
bool mem1;
namespace FastMod{
	inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
	inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
	inline void mmul(int &x,int y){x=1ull*x*y%mod;}
	inline int imadd(int x,int y){madd(x,y);return x;}
	inline int imdel(int x,int y){mdel(x,y);return x;}
	inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace FastMod;
namespace MATT{
	const int maxn=5010;
	int n,l,r,sum;
	int a[maxn],b[maxn],dp[maxn][maxn],g[maxn][maxn];
	int sa[maxn],sb[maxn];
	int DP(int x){
		if(x<0)	return 0;
		mems(dp,0);
		dp[1][0]=1;for(int i=0;i<=n;i++)g[1][i]=1;
		for(int i=2,k=0;i<=n;i++){
			while(k<=n&&sa[i-1]-sb[k]>x)	k++;
    		for(int j=0;j<i;j++){
                if(sa[i]-sb[j]>x)   continue;
    			// for(int k=0;k<=i-2&&k<=j;k++){
    			// 	if(sa[i-1]-sb[k]<=x)	madd(dp[i][j],dp[i-1][k]);
    			// }
				for(int k=0;k<=min(i-2,j);k++)
					if(sa[i-1]-sb[k]<=x)	madd(dp[i][j],dp[i-1][k]);
					else	madd(dp[i][j],dp[i-1][k]);
				if(min(i-2,j)>=k)	madd(dp[i][j],imdel(g[i-1][min(i-2,j)],k?g[i-1][k-1]:0));
    		}
			g[i][0]=dp[i][0];
			for(int j=1;j<=n;j++)	g[i][j]=imadd(g[i][j-1],dp[i][j]);
    	}
    	int ret=0;
    	for(int i=0;i<n;i++)	madd(ret,dp[n][i]);
    	return ret;
	}
    void matt(){
    	scanf("%d%d%d",&n,&l,&r);
    	for(int i=1;i<=n;i++)	scanf("%d",&a[i]),sum-=a[i];
    	for(int i=1;i<=n;i++)	scanf("%d",&b[i]),sum+=b[i];
		for(int i=1;i<=n;i++)	sa[i]=sa[i-1]+a[i],sb[i]=sb[i-1]+b[i];
    	printf("%d\n",imdel(DP(r-sum),DP(l-sum-1)));
    }
}
bool mem2;
int main(){
	#ifdef LOCAL
	freopen("code.in","r",stdin);freopen("code.out","w",stdout);
	#endif
	double sta=clock();
	int T=1;while(T--)MATT::matt();
	debug("%.2fMB,%.0fms\n",abs(&mem1-&mem2)/1024./1024,(clock()-sta)/CLOCKS_PER_SEC*1000);
}