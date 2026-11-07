#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define pii pair<int,int>
#define fi first
#define se second
#define eb emplace_back
#define ep emplace
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
bool mem1;
namespace OIMATT{
	const int maxn=5e5+10,maxm=501;
	int C,n,m,d,q;
	int a[maxn];
	ll f[maxm][maxm];
	vector<pii> son[maxn];
	vector<int> vG[maxm];
	int G[maxm][maxn];
	inline void gmn(ll &x,ll y){(x>y)&&(x=y);}
	void solve(int _c){
		cin>>C>>m>>n>>d>>q;
		for(int i=1;i<=n;i++)	cin>>a[i];
		for(int i=1;i<=m;i++){
			int k;cin>>k;
			while(k--){
				int u,t;cin>>u>>t;
				son[u].eb(i,t);
				G[i][u]=t;vG[i].eb(u);
			}
		}
		mems(f,0x3f);for(int i=1;i<=m;i++)f[i][i]=0;
		for(int i=1;i<=m;i++){
			for(int k:vG[i]){
				for(int j=i+1;j<=m;j++)if(G[j][k])gmn(f[i][j],G[i][k]+G[j][k]);
			}
		}
		for(int i=1;i<=m;i++)for(int j=i+1;j<=m;j++)f[j][i]=f[i][j];
		for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)for(int k=1;k<=m;k++)gmn(f[j][k],f[j][i]+f[i][k]);
		while(q--){
			int s,t;cin>>s>>t;
			ll ans=4e18;
			for(pii i:son[s]){
				for(pii j:son[t]){
					gmn(ans,i.se+f[i.fi][j.fi]+j.se);
				}
			}
			cout<<ans+a[s]+a[t]<<'\n';
		}
	}
}
bool mem2;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
	int T=1;for(int i=1;i<=T;i++)OIMATT::solve(i);
	debug("%.0fms\n",double(clock())/CLOCKS_PER_SEC*1000);
}