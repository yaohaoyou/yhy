#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10,maxm=2e5+10;
int n,m;
int deg[maxn][2];
bool vis[maxn][2],vis2[maxn][2];
namespace Graph{
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v][0]++;deg[v][1]++;}
}
using namespace Graph;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        add(v,u);
    }
    function<void(int,bool)>dfs=[&dfs](int u,bool f){
        vis[u][f]=true;
        go(u,i){
            int v=e[i].to;
            --deg[v][f^1];
            if(!f&&!vis[v][1])  dfs(v,1);
            if(f&&!deg[v][0])   dfs(v,0);
        }
    };
    for(int i=1;i<=n;i++)
        if(!deg[i][0]&&!vis[i][0])  dfs(i,0);
    memc(vis2,vis);
    for(int i=1;i<=n;i++)
        if(!deg[i][1]&&!vis[i][1])  dfs(i,1);
    for(int o:{0,1}){
        for(int u=1;u<=n;u++)
            printf(vis[u][o]?(vis2[u][o]^o)?"L":"W":"D");
        puts("");
    }
}