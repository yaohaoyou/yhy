#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pli pair<ll,int>
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
bool mem1;
namespace OIMATT{
	const int maxk=60,maxn=510+10,maxp=maxn*maxn+maxk,dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
	int n,m,q,tot,TOT,d;
	int a[maxn][maxn],b[maxn][maxn],id[maxn][maxn];
	ll dis[maxp];bool vis[maxp];
	ll dp[maxk<<1][maxk<<1],dd[maxk][maxk];
	piii nw[maxk];
	vector<pii> son[maxp];
	vector<int> v[maxk];
	priority_queue<pli,vector<pli>,greater<pli>> pq;
	stack<int> stk;
	inline void gmn(ll &x,ll y){(x>y)&&(x=y);}
	inline void gmx(ll &x,ll y){(x<y)&&(x=y);}
	inline void add(int u,int v,int w){son[u].eb(v,w);stk.ep(u);}
	inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
	inline pii P(int p){
		if(p<=m)	return pii(0,p);
		if(p<=m+n)	return pii(p-m,m);
		if(p<=m+m+n)	return pii(n,m-(p-m-n));
		return pii(n-(p-m-m-n),0);
	}
	void dijkstra(int o){
		mems(dis,0x3f);mems(vis,0);
        for(int s:v[o]) pq.ep(dis[s]=0,s);
		while(!pq.empty()){
			int u=pq.top().se;pq.pop();if(vis[u])continue;vis[u]=true;
			for(pii tmp:son[u]){
				int t=tmp.fi,w=tmp.se;
				if(dis[t]>dis[u]+w&&!vis[t])	pq.ep(dis[t]=dis[u]+w,t);
			}
		}
        for(int j=0;j<tot-TOT;j++){
            dd[o][j]=1e18;
            for(int l:v[j]) gmn(dd[o][j],dis[l]);
        }
	}
	void matt(){
		scanf("%d%d%d",&n,&m,&q);
		for(int i=1;i<n;i++)for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);
		for(int i=1;i<=n;i++)for(int j=1;j<m;j++)scanf("%d",&b[i][j]);
		for(int i=0;i<=n;i++)for(int j=0;j<=m;j++)id[i][j]=++tot;
		for(int i=0;i<n;i++)
			for(int j=1;j<m;j++)	adde(id[i][j],id[i+1][j],b[i+1][j]);
		for(int j=0;j<m;j++)
			for(int i=1;i<n;i++)	adde(id[i][j],id[i][j+1],a[i][j+1]);
		while(!stk.empty())stk.pop();
        TOT=tot;
		while(q--){
			int k;scanf("%d",&k);
			int lc=-1,nx,ny;d=0;
			for(int i=1;i<=k;i++)	scanf("%d%d%d",&nw[i].fi.se,&nw[i].fi.fi,&nw[i].se);
			bool flag=true;for(int i=1;i<=k;i++)flag&=nw[1].se==nw[i].se;
			if(flag){puts("0");continue;}
			sort(nw+1,nw+k+1);
			nx=P(nw[k].fi.fi).fi,ny=P(nw[k].fi.fi).se;lc=nw[k].se;
			for(int i=1;i<=k;i++){
				int w=nw[i].fi.se,p=nw[i].fi.fi,col=nw[i].se;
				if(p<=m)	adde(id[0][p-1],id[0][p],w);
				else if(p<=m+n)	adde(id[p-m-1][m],id[p-m][m],w);
				else if(p<=m+m+n)	adde(id[n][m-(p-m-n)],id[n][m-(p-m-n)+1],w);
				else	adde(id[n-(p-m-m-n)][0],id[n-(p-m-m-n)+1][0],w);
				int x=P(p).fi,y=P(p).se;
				if(col!=lc){
					// printf("%d %d -> %d %d : %d %d\n",nx,ny,x,y,id[nx][ny],id[x][y]);
					++tot;int cnt=0;
					if(!nx)	d=1;
					else if(ny==m)	d=2;
					else if(nx==n)	d=3;
					else d=0;
					while((nx^x)||(ny^y)){
						while(nx+dir[d][0]>=0&&nx+dir[d][0]<=n&&ny+dir[d][1]>=0&&ny+dir[d][1]<=m){
							// printf("(%d,%d)\n",nx,ny);
							adde(tot,id[nx][ny],0);v[tot-TOT-1].eb(id[nx][ny]);
							// printf("add %d %d %d\n",nx,ny,tot);
							nx+=dir[d][0];ny+=dir[d][1];
							if(nx==x&&ny==y)	break;
						}
						if(nx==x&&ny==y)	break;
						d=(d+1)&3;
					}
					// puts("");
				}
                else{
					if(!nx)	d=1;
					else if(ny==m)	d=2;
					else if(nx==n)	d=3;
					else d=0;
					// printf("%d %d -> %d %d : %d %d\n",nx,ny,x,y,id[nx][ny],id[x][y]);
                    while((nx^x)||(ny^y)){
						while(nx+dir[d][0]>=0&&nx+dir[d][0]<=n&&ny+dir[d][1]>=0&&ny+dir[d][1]<=m){
							// printf("(%d,%d)\n",nx,ny);
							if(nx+dir[d][0]!=x||ny+dir[d][1]!=y)adde(id[nx][ny],id[nx+dir[d][0]][ny+dir[d][1]],0);
							// printf("add %d %d %d %d %d\n",nx,ny,nx+dir[d][0],ny+dir[d][1],d);
							nx+=dir[d][0];ny+=dir[d][1];
							if(nx==x&&ny==y)	break;
						}
						if(nx==x&&ny==y)	break;
						d=(d+1)&3;
					}
                }
				lc=col;
			}
			k=tot-TOT;
			for(int i=0;i<k;i++)	dijkstra(i);
			const int K=k<<1;
			mems(dp,0x3f);
			for(int i=0;i<K;i++)	dp[i+1][i]=0;
			for(int i=2;i<=k;i+=2){
				for(int l=0,r=i-1;r<K;l++,r++){
					gmn(dp[l][r],dp[l+1][r-1]+dd[l%k][r%k]);
					for(int j=l+1;j<=r;j+=2)	gmn(dp[l][r],dp[l+1][j-1]+dp[j+1][r]+dd[l%k][j%k]);
                    for(int j=l+1;j<=r;j+=2)    gmn(dp[l][r],dp[l][j]+dp[j+1][r]);
				}
			}
			ll ans=1e18;
			for(int i=0;i<k;i++)	gmn(ans,dp[i][i+k-1]);
			printf("%lld\n",ans);
			while(!stk.empty())	son[stk.top()].pop_back(),stk.pop();
			tot=TOT;for(int i=0;i<k;i++)v[i].clear();
		}
	}
}
bool mem2;
int main(){
	debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
	double sta=clock();
	int T=1;while(T--)OIMATT::matt();
	debug("%.0fms\n",(clock()-sta)/CLOCKS_PER_SEC*1000);
}