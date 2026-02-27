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
const int maxn=1e5+10,maxk=410,mod=998244353;
int n,m,k;
bool a[maxn];
namespace Graph{
	const int maxm=maxn<<1;
	#define go(x,i) for(int i=head[x];i;i=e[i].nxt)
	int cnt=1;
	int head[maxn];
	struct edge{int nxt,to;}e[maxm];
	inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
	inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
namespace FastMod{
	inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
	inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
	inline void mmul(int &x,int y){x=1ll*x*y%mod;}
	inline int imadd(int x,int y){madd(x,y);return x;}
	inline int imdel(int x,int y){mdel(x,y);return x;}
	inline int immul(int x,int y){mmul(x,y);return x;}
	inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
int ban;
int dp[maxn],f[maxn][2],g[maxk];
int fac[maxn],inv[maxn],stir[maxk][maxk];
void dfs(int u,int fa){
	f[u][0]=1;f[u][1]=bool(!a[u]);
	go(u,i){
		int t=e[i].to;
		if(t==fa)	continue;
		dfs(t,u);
		mmul(f[u][0],imadd(immul(f[t][0],m-1-ban),immul(f[t][1],ban)));
		mmul(f[u][1],imadd(immul(f[t][0],m-ban),immul(f[t][1],ban-1)));
	}
}
void init(){
	int N=max({n,m,k});
	fac[0]=1;
	for(int i=1;i<=N;i++)	fac[i]=immul(fac[i-1],i);
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;~i;i--)	inv[i]=immul(inv[i+1],i+1);
	for(int i=0;i<=k;i++){
		stir[i][0]=!i;
		for(int j=1;j<=i;j++)	stir[i][j]=imadd(immul(stir[i-1][j],j),stir[i-1][j-1]);
	}
}
inline int C(int x,int y){return x<y?0:1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
	int sizS;
	scanf("%d%d%d%d",&n,&m,&k,&sizS);
	init();
	while(sizS--){int x;scanf("%d",&x);a[x]=true;}
	for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
	for(ban=0;ban<=k;ban++){
		dfs(1,0);
		dp[ban]=imadd(immul(f[1][0],m-ban),immul(f[1][1],ban));
	}
	for(int i=0;i<=k;i++){
		for(int j=0;j<=i;j++){
			if(j&1)	mdel(g[i],immul(C(i,j),dp[j]));
			else	madd(g[i],immul(C(i,j),dp[j]));
		}
		mmul(g[i],C(m,i));
	}
	int ans=0;
	for(int i=0;i<=k;i++)
		madd(ans,immul(immul(stir[k][i],fac[i]),g[i]));
	printf("%d\n",ans);
}