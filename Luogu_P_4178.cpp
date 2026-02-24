#include <bits/stdc++.h>
using namespace std;
const int maxn=4e4+10;
int n,m,ans;
int tot=1,head[maxn];
struct Edge{int nxt,to,w;}e[maxn<<1];
void add_edge(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int sum,mn,root,siz[maxn],vis[maxn<<1];
void getroot(int u,int fr)
{
	int mx=0;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;if(i==(fr^1)||vis[i]) continue;
		getroot(v,i);siz[u]+=siz[v];
	}
	mx=max(siz[u],sum-siz[u]);
	if(mx<mn) root=fr,mn=mx;
}
int dis[maxn];
vector<int> vec[2];
#define eb emplace_back
void dfs(int u,int fa,int id)
{
	vec[id].eb(u);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;if(v==fa||vis[i]) continue;
		dis[v]=dis[u]+e[i].w;dfs(v,u,id);
	}
}
int calc(int E)
{
	int u=e[E^1].to,v=e[E].to,res=0;
    dis[u]=dis[v]=0;
	vec[0].clear();dfs(u,v,0);
    vec[1].clear();dfs(v,u,1);
	sort(vec[0].begin(),vec[0].end(),[&](int x,int y){return dis[x]<dis[y];});
	sort(vec[1].begin(),vec[1].end(),[&](int x,int y){return dis[x]<dis[y];});
    for(int i=0;i<vec[1].size();i++){vec[1][i]=dis[vec[1][i]];/*printf("%d ",vec[1][i]);*/}
    // puts("");
	for(int i:vec[0])
	{
        int j=upper_bound(vec[1].begin(),vec[1].end(),m-dis[i]-e[E].w)-vec[1].begin();
        // printf("%d %d\n",m-dis[i]-e[E].w,j);
        res+=j;
	}
    // puts("\n");
	return res;
}
void solve(int E)
{
	int u=e[E^1].to,v=e[E].to;
	vis[E]=vis[E^1]=1;ans+=calc(E);
	sum=sum-siz[v];
	if(sum!=1){
        mn=1e9;getroot(u,(E^1));
        solve(root);
    }
	sum=siz[v];
    if(sum!=1){
        mn=1e9;getroot(v,E);
	    solve(root);
    }
}
int main()
{
	scanf("%d",&n);
	for(int i=1,x,y,z;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	scanf("%d",&m);
	sum=n;mn=1e9;getroot(1,0);solve(root);
	printf("%d",ans);
}