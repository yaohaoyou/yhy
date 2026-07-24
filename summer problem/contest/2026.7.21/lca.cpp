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
int n;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int siz[maxn],fa[maxn];
ll f[maxn];
void dfs1(int u,int ft){siz[u]=1;fa[u]=ft;go(u,i)if(t^ft)dfs1(t,u),siz[u]+=siz[t];}
void dfs(int u,int ft){
    if(ft){
        f[u]=f[ft]-1ll*n*n*ft-1ll*siz[u]*siz[u]*(u-ft);
        int sz=n-siz[u];
        f[u]+=1ll*sz*sz*(ft-u)+1ll*n*n*u;
    }
    go(u,i)if(t^ft)dfs(t,u);
}
int main(){
    freopen("lca.in","r",stdin);freopen("lca.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs1(1,0);
    for(int i=1;i<=n;i++)   f[1]+=1ll*siz[i]*siz[i]*(i-fa[i]);
    dfs(1,0);
    for(int i=1;i<=n;i++)   printf("%lld ",f[i]);
}