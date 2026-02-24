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
const int maxn=510<<1;
int n,m,E;
int a[maxn];
namespace Graph{
    const int maxm=1e5+10;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
int p[maxn],to[maxn];
bool vis[maxn];
bool dfs(int u){
    go(u,i){
        if(vis[t])  continue;
        vis[t]=true;
        if(!p[t]||dfs(p[t]))    return p[t]=u,true;
    }
    return false;
}
int main(){
    scanf("%d%d%d",&n,&m,&E);
    for(int i=1;i<=E;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v+n);}
    int ans=0;
    for(int i=1;i<=n;i++)   mems(vis,0),ans+=dfs(i);
    printf("%d\n",ans);
}