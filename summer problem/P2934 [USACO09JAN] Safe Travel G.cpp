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
const int maxn=1e5+10;
int n,m;
vector<int> vec[maxn];
namespace Graph{
    const int maxm=4e5+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
int dp[maxn],fa[maxn];
bool vis[maxn];
priority_queue<pii,vector<pii>,greater<pii>> q;
void dijkstra(int s){
    mems(dp,0x3f);q.ep(dp[s]=0,s);
    while(!q.empty()){
        int u=q.top().se;q.pop();if(vis[u])continue;vis[u]=true;
        go(u,i)if(dp[t]>dp[u]+w){dp[t]=dp[u]+w;fa[t]=u;q.ep(dp[t],t);}
    }
}
int tot;
int ans[maxn],dfsn[maxn],rnk[maxn],siz[maxn],son[maxn],tp[maxn],dep[maxn];
vector<int> ins[maxn],era[maxn];
multiset<int> st;
void dfs1(int u){
    siz[u]=1;
    for(int t:vec[u]){
        dep[t]=dep[u]+1;
        dfs1(t);
        siz[u]+=siz[t];
        if(siz[t]>siz[son[u]])  son[u]=t;
    }
}
void dfs2(int u){
    dfsn[u]=++tot;rnk[tot]=u;
    if(son[u])  tp[son[u]]=tp[u],dfs2(son[u]);
    for(int t:vec[u]){
        if(t==son[u])   continue;
        tp[t]=t;dfs2(t);
    }
}
inline int LCA(int x,int y){
    while(tp[x]^tp[y]){
        if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
        x=fa[tp[x]];
    }
    return dep[x]<dep[y]?x:y;
}
inline int jump(int x,int y){
    while(tp[x]^tp[y]){
        if(fa[tp[x]]==y)    return tp[x];
        x=fa[tp[x]];
    }
    return son[y];
}
inline void upd(int x,int y,int s){
    while(tp[x]^tp[y]){
        if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
        ins[dfsn[tp[x]]].eb(s);era[dfsn[x]+1].eb(s);
        x=fa[tp[x]];
    }
    if(dfsn[x]>dfsn[y]) swap(x,y);
    ins[dfsn[x]].eb(s);era[dfsn[y]+1].eb(s);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);}
    dijkstra(1);
    for(int i=2;i<=n;i++)   vec[fa[i]].eb(i);
    dfs1(1);tp[1]=1;dfs2(1);
    for(int u=1;u<=n;u++){
        go(u,i){
            if(fa[u]==t||fa[t]==u)  continue;
            int U=u;
            int l=LCA(u,t);
            if(t==l)    continue;
            upd(jump(t,l),t,dp[u]+w+dp[t]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j:ins[i])   st.ep(j);
        for(int j:era[i])   st.erase(st.find(j));
        ans[rnk[i]]=st.empty()?-1:*st.begin()-dp[rnk[i]];
    }
    for(int i=2;i<=n;i++)   printf("%d\n",ans[i]);
}