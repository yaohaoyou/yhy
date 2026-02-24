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
const int maxn=3e6+10;
int n,seed;
int a[maxn];
ll ans;
ll f[maxn],c[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
namespace Generate{
	static const int mod=1e9;
	int Rand(int x){
		seed=(1ll*seed*0x66CCF+19260817ll)%x+1;
		seed=(1ll*seed*0x77CCF+20060428ll)%x+1;
		seed=(1ll*seed*0x88CCF+12345678ll)%x+1;
		seed=(1ll*seed*0x33CCCCFF+10086001ll)%x+1;
		return seed;
	}
	void RS(int* a){ //你需要传入三个参数，分别表示点权，一条边的两个端点 
		int cnt=0;
		for(int i=1;i<=n;i++)a[i]=Rand(mod); 
		for(int i=2;i<=n;i++){
			int fa=Rand(i-1);
            adde(fa,i);
		}
	}
};
void dfs(int u,int ft){
    ll sum=0,mx=-1e18;
    go(u,i)if(t^ft)dfs(t,u),sum+=f[t],mx=max(mx,f[t]);
    if(mx==-1e18){f[u]=a[u];c[u]=0;ans+=max(a[u]-sum,-c[u]);return;}
    c[u]=max(0ll,min({(ll)a[u],sum-a[u],sum/2,sum-mx}));
    f[u]=a[u]-c[u];
    ans+=max(a[u]-sum,-c[u]);
}
int main () {
	int op;
	scanf("%d",&op);
	if(op==1){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
        for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
	}else{
		scanf("%d %d",&seed,&n);
		Generate::RS(a);
	}
    dfs(1,0);
    printf("%lld\n",ans);
}