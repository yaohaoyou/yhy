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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n,m,S,T;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int f[maxn],g[maxn],p[maxn];
bool vis[maxn];
priority_queue<pii,vector<pii>,greater<pii>> q;
void dijkstra(){
    mems(f,0x3f);
    q.ep(f[S]=0,S);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=true;
        go(u,i){
            if(f[t]>f[u]+1){
                p[t]=u;
                f[t]=f[u]+1;
                if(!vis[t])q.ep(f[t],t);
            }
        }
    }
}
void dijkstra2(){
    mems(g,0x3f);mems(vis,0);
    q.ep(g[T]=0,T);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=true;
        go(u,i){
            if(g[t]>g[u]+1){
                g[t]=g[u]+1;
                if(!vis[t])q.ep(g[t],t);
            }
        }
    }
}
int bel[maxn];
void dfs(int u){
    vis[u]=true;
    go(u,i)if(!vis[t]&&f[t]==f[u]+1){
        bel[t]=bel[u];
        vis[t]=true;
        dfs(t);
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dijkstra();dijkstra2();
    int ans=1e9;
    mems(vis,0);
    vector<int> path;
    for(int i=p[T];i^S;i=p[i]){if(deg[i]>=3)gmn(ans,f[T]*2+2);vis[i]=true;path.eb(i);}
    path.eb(S);path.eb(T);vis[S]=vis[T]=true;
    for(int u:path) bel[u]=u,dfs(u);
    mems(vis,0);for(int i:path)vis[i]=true;
    for(int i=2;i<=cnt;i++){
        int u=e[i].to,v=e[i^1].to;
        if(vis[u]&&vis[v])  continue;
        if(bel[u]==bel[v])  continue;
        gmn(ans,f[T]+f[u]+1+g[v]);
    }
    for(int i=1;i<=n;i++)if(deg[i]>=3)gmn(ans,(f[i]+g[i]+2)*2);
    if(ans>=10*n)  ans=-1;
    printf("%d\n",ans);
}