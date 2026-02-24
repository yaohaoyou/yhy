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
const int maxn=5e5+10;
int n,k;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
priority_queue<pii,vector<pii>,greater<pii>> pq;
bool vis[maxn];
int dis[maxn],a[maxn],dep[maxn];
void dijkstra(){
    while(!pq.empty()){
        int u=pq.top().se;pq.pop();if(vis[u])continue;vis[u]=true;
        go(u,i)if(dis[t]>dis[u]+1){dis[t]=dis[u]+1;pq.ep(dis[t],t);}
    }
}
int fa[maxn];
bool mk[maxn];
void dfs(int u,int ft){dep[u]=dep[fa[u]=ft]+1;go(u,i)if(t^ft)dfs(t,u);}
void dfs2(int u,int ft,int lst){
    if(mk[u])return;mk[u]=true;
    if(!lst)    return;
    go(u,i)if(dis[t]==lst-1)dfs2(t,u,lst-1);
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    mems(dis,0x3f);
    for(int i=1;i<=k;i++){scanf("%d",&a[i]);pq.ep(dis[a[i]]=0,a[i]);}
    dijkstra();
    dfs(1,0);
    sort(a+1,a+k+1,[&](int x,int y){return dep[x]>dep[y];});
    vector<int> ans;
    for(int i=1;i<=k;i++){
        int x=a[i];
        if(mk[x])   continue;
        while(fa[x]&&dis[fa[x]]==dep[a[i]]-dep[fa[x]]) x=fa[x];
        // printf("%d %d %d %d\n",a[i],x,fa[x],dis[fa[x]]);
        dfs2(x,0,dis[x]);
        ans.eb(x);
    }
    printf("%d\n",ans.size());
    for(int i:ans)  printf("%d ",i);puts("");
}