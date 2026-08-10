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
const int maxn=2000+10;
const int INF=1e9;
int n,m;
vector<int> vec[maxn];
namespace Graph{
    const int maxm=2e5+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    void rebuild(){for(int i=1;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int ans[maxn];
int dp[2][maxn];
int fa[2][maxn],fr[maxn];
int f[maxn],g[maxn];
bool ontr[maxm];
vector<int> ins[maxn],era[maxn];
multiset<int> st;
bool vis[maxn];
int id[maxn];
int mp[maxn][maxn];
priority_queue<pii,vector<pii>,greater<pii>> q;
void dijkstra(int s,bool o){
    for(int i=1;i<=n;i++)dp[o][i]=INF,vis[i]=false;
    q.ep(dp[o][s]=0,s);
    while(!q.empty()){
        int u=q.top().se;q.pop();if(vis[u])continue;vis[u]=true;
        go(u,i)if(dp[o][t]>dp[o][u]+w){dp[o][t]=dp[o][u]+w;fa[o][t]=u;if(!o)fr[t]=i;q.ep(dp[o][t],t);}
    }
}
void dfs1(int u){if(id[u])f[u]=id[u];for(int t:vec[u]){f[t]=f[u];dfs1(t);}}
void dfs2(int u){if(id[u])g[u]=id[u];for(int t:vec[u]){g[t]=g[u];dfs2(t);}}
void matt(){
    int S,T;
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        adde(u,v,w);
        if(!mp[u][v]||e[mp[u][v]<<1].w>w)mp[u][v]=mp[v][u]=i;
    }
    dijkstra(S,0);dijkstra(T,1);
    int tot=0;vector<int> lst;lst.clear();
    {
        int u=T;
        while(u){lst.eb(u);ontr[fr[u]>>1]=true;u=fa[0][u];}
        reverse(lst.begin(),lst.end());
        for(int i:lst)    id[i]=++tot;
    }
    for(int i=1;i<=n;i++)   if(i^S)vec[fa[0][i]].eb(i);dfs1(S);
    for(int i=1;i<=n;i++)   vec[i].clear();
    for(int i=1;i<=n;i++)   if(i^T)vec[fa[1][i]].eb(i);dfs2(T);
    for(int i=1;i<=n;i++)   vec[i].clear();
    for(int i=1;i<=m;i++){
        if(ontr[i]) continue;
        int u=e[i<<1].to,v=e[i<<1|1].to,w=e[i<<1].w;
        if(f[u]<g[v]){ins[f[u]+1].eb(dp[0][u]+w+dp[1][v]);era[g[v]+1].eb(dp[0][u]+w+dp[1][v]);}
        swap(u,v);
        if(f[u]<g[v]){ins[f[u]+1].eb(dp[0][u]+w+dp[1][v]);era[g[v]+1].eb(dp[0][u]+w+dp[1][v]);}
    }
    int k;scanf("%d",&k);
    vector<int> vv;vv.clear();for(int i=1;i<=k;i++){int x;scanf("%d",&x);vv.eb(x);}
    for(int i=1;i<=tot;i++){
        for(int j:ins[i])   st.ep(j);
        for(int j:era[i]){
            if(st.find(j)==st.end())    exit(0);
            st.erase(st.find(j));
        }
        if(i^1) ans[mp[lst[i-2]][lst[i-1]]]=st.empty()?-1:*st.begin();
    }
    for(int i=2;i<=k;i++){
        int u=vv[i-2],v=vv[i-1];
        if(!ontr[mp[u][v]]) printf("%d\n",dp[0][T]);
        else    printf("%d\n",ans[mp[u][v]]);
    }
}
int main(){int T=1;while(T--)matt();}