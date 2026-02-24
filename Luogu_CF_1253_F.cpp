#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e5+10;
int n,m,q,k;
namespace Graph{
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    const int maxm=6e5+2e5+10;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,fr,to;ll w;}e[maxm];
    inline void add(int u,int v,ll w){e[++cnt]={head[u],u,v,w};head[u]=cnt;}
    inline void adde(int u,int v,ll w){add(u,v,w);add(v,u,w);}
    vector<pli> son[maxn];
}
using namespace Graph;
ll dis[maxn];
bool vis[maxn];
priority_queue<pli,vector<pli>,greater<pli>> pq;
void dijkstra(){
    mems(dis,0x3f);
    dis[0]=0;
    pq.emplace(0,0);
    while(!pq.empty()){
        int u=pq.top().se;pq.pop();
        if(vis[u])  continue;
        vis[u]=true;
        go(u,i){
            int t=e[i].to;
            if(dis[u]+e[i].w<dis[t]){dis[t]=dis[u]+e[i].w;if(!vis[t])pq.emplace(dis[t],t);}
        }
    }
}
int fa[maxn];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void kruskal(){
    for(int i=1;i<=n;i++)   fa[i]=i;
    int tot=0;
    sort(e+2,e+cnt+1,[&](edge x,edge y){return x.w<y.w;});
    for(int i=2;i<=cnt;i++){
        int u=e[i].fr,v=e[i].to;ll w=e[i].w;
        if(!u||!v)  continue;
        if(find(u)==find(v))    continue;
        tot++;
        fa[find(u)]=find(v);
        son[u].eb(w,v);son[v].eb(w,u);
        if(tot==n-1)    return;
    }
}
int dep[maxn],f[20][maxn];
ll W[20][maxn];
void dfs(int u,int fa){
    dep[u]=dep[f[0][u]=fa]+1;
    for(auto [w,t]:son[u]){
        if(t==fa)   continue;
        W[0][t]=w;
        dfs(t,u);
    }
}
void init(){for(int i=1;i<20;i++)for(int j=1;j<=n;j++)f[i][j]=f[i-1][f[i-1][j]],W[i][j]=max(W[i-1][j],W[i-1][f[i-1][j]]);}
inline ll getans(int u,int v){
    ll ans=0;
    if(dep[u]<dep[v])   swap(u,v);
    for(int i=19;~i;i--){
        if(dep[f[i][u]]>=dep[v]){
            ans=max(ans,W[i][u]);
            u=f[i][u];
        }
    }
    if(u==v)    return ans;
    for(int i=19;~i;i--){
        if(f[i][u]^f[i][v]){
            ans=max(ans,W[i][u]);ans=max(ans,W[i][v]);
            u=f[i][u];v=f[i][v];
        }
    }
    ans=max(ans,W[0][u]);ans=max(ans,W[0][v]);
    return ans;
}
int main(){
    scanf("%d%d%d%d",&n,&m,&k,&q);
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        adde(u,v,w);
    }
    for(int i=1;i<=k;i++) adde(0,i,0);
    dijkstra();
    for(int i=2;i<=cnt;i++) e[i].w+=dis[e[i].to]+dis[e[i].fr];
    kruskal();
    dfs(1,0);
    init();
    while(q--){int u,v;scanf("%d%d",&u,&v);printf("%lld\n",getans(u,v));}
}