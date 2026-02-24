#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10;
int n,m;
namespace Graph{
    const int maxm=8e5+10;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;bool ontr;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w,false};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
ll dis[2][maxn];
int pre[2][maxn],id[2][maxn];
bool vis[maxn];
priority_queue<pli,vector<pli>,greater<pli>> q;
vector<int> pas[2];
void dijkstra(int s,bool o){
    mems(dis[o],0x3f);mems(vis,0);
    dis[o][s]=0;
    q.ep(0,s);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])  continue;
        vis[u]=true;
        go(u,i){
            int t=e[i].to;
            if(dis[o][t]>dis[o][u]+e[i].w){
                dis[o][t]=dis[o][u]+e[i].w;
                pre[o][t]=i;
                q.ep(dis[o][t],t);
            }
        }
    }
}
void getpass(int o,int u){
    pas[o].eb(0);
    while(u^(o?1:n)){
        pas[o].eb(u);
        e[pre[!o][u]].ontr=e[pre[!o][u]^1].ontr=true;
        u=e[pre[!o][u]^1].to;
    }
    pas[o].eb(u);
}
void dfs(int u,int fa,bool o,int x){
    id[o][u]=x;
    go(u,i){
        int t=e[i].to;
        if(t==fa||id[o][t]||dis[o][t]!=dis[o][u]+e[i].w)   continue;
        dfs(t,u,o,x);
    }
}
multiset<int> ad[maxn],er[maxn],s;
ll ans1;int ans2;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        adde(u,v,w);
    }
    dijkstra(1,0);dijkstra(n,1);
    getpass(0,1);getpass(1,n);
    for(int i=1;i<pas[0].size();i++)    id[0][pas[0][i]]=i;
    for(int i=1;i<pas[0].size();i++)    id[1][pas[0][i]]=pas[0].size()-i;
    for(int i=1;i<pas[0].size();i++){
        dfs(pas[0][i],0,0,i);
    }
    for(int i=pas[0].size()-1;i;i--){
        dfs(pas[0][i],0,1,i);
    }
    // for(int i=1;i<=n;i++)   printf("%d %d\n",id[0][i],id[1][i]);
    for(int i=2;i<=cnt;i++){
        if(e[i].ontr)   continue;
        int u=e[i^1].to,v=e[i].to,w=e[i].w;
        ll res=dis[0][u]+w+dis[1][v];
        if(v==1||u==n)  continue;
        int l=id[0][u],r=id[1][v]-1;
        if(l>r) continue;
        // printf("(%d,%d,%d)\n",u,v,w);
        // printf("[%d,%d] : %d\n",id[0][u]+1,pas[0].size()-id[1][v],res);
        // printf("[%d,%d] : %d\n",l,r,res);
        if(l<=r){ad[l].ep(res);er[r].ep(res);}
    }
    for(int i=1;i<pas[0].size();i++){
        for(int j:ad[i])    s.ep(j);
        if(!s.empty()){
            int k=*s.begin();
            if(ans1<k)  ans1=k,ans2=0;
            if(ans1==k) ans2++;
        }
        for(int j:er[i])    s.erase(s.find(j));
    }
    if(ans1==dis[0][n]) ans2=m;
    printf("%lld %d\n",ans1,ans2);
}