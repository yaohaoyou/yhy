#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=3e5+10;
const ll INF=1e18;
int n,m;
vector<int> vec[maxn];
namespace Graph{
    const int maxm=6e5+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    void rebuild(){for(int i=1;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
ll dp[2][maxn];
int fa[2][maxn],fr[maxn];
int f[maxn],g[maxn];
bool ontr[maxn];
vector<int> ins[maxn],era[maxn];
multiset<int> st;
bool vis[maxn];
int id[maxn];
priority_queue<pli,vector<pli>,greater<pli>> q;
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
    rebuild();for(int i=0;i<=n;i++) id[i]=ontr[i]=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);}
    dijkstra(1,0);dijkstra(n,1);
    int tot=0;vector<int> lst;lst.clear();
    {
        int u=n;
        while(u){lst.eb(u);ontr[fr[u]>>1]=true;u=fa[0][u];}
        reverse(lst.begin(),lst.end());
        for(int i:lst)    id[i]=++tot;
    }
    // for(int i=2;i<=n;i++)   printf("fa[%d] = %d %d\n",i,fa[0][i],fa[1][i]);
    for(int i=2;i<=n;i++)   vec[fa[0][i]].eb(i);dfs1(1);
    for(int i=1;i<=n;i++)   vec[i].clear();
    for(int i=1;i<n;i++)    vec[fa[1][i]].eb(i);dfs2(n);
    for(int i=1;i<=n;i++)   vec[i].clear();
    // for(int i=1;i<=n;i++)   printf("%d %d\n",f[i],g[i]);
    // for(int i=1;i<=n;i++){
    //     if(dp[0][i]+dp[1][i]==dp[0][n]){ins[f[i]+1].eb(-1);era[g[i]+1].eb(-1);}
    //     else if(dp[0][i]+dp[1][i]==dp[0][n]+1){ins[f[i]+1].eb(1);era[g[i]+1].eb(1);}
    // }
    for(int i=1;i<=m;i++){
        if(ontr[i]) continue;
        int u=e[i<<1].to,v=e[i<<1|1].to,w=e[i<<1].w;
        if(dp[0][u]+w+dp[1][v]==dp[0][n]){ins[f[u]+1].eb(-1);era[g[v]+1].eb(-1);}
        else if(dp[0][u]+w+dp[1][v]==dp[0][n]+1){ins[f[u]+1].eb(1);era[g[v]+1].eb(1);}
        swap(u,v);
        if(dp[0][u]+w+dp[1][v]==dp[0][n]){ins[f[u]+1].eb(-1);era[g[v]+1].eb(-1);}
        else if(dp[0][u]+w+dp[1][v]==dp[0][n]+1){ins[f[u]+1].eb(1);era[g[v]+1].eb(1);}
    }
    vector<int> ans;ans.clear();
    for(int i=1;i<=tot;i++){
        for(int j:ins[i])   st.ep(j);ins[i].clear();
        for(int j:era[i])   st.erase(st.find(j));era[i].clear();
        if(!st.empty()&&*st.begin()==1) ans.eb(fr[lst[i-1]]>>1);
    }
    ins[tot+1].clear();era[tot+1].clear();st.clear();
    sort(ans.begin(),ans.end());
    printf("%d\n",ans.size());
    for(int i:ans)  printf("%d ",i);puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}