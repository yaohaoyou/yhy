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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=8010,maxm=810;
int n,m;
namespace Graph{
    const int maxe=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxe];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline void upd(int l,int r,int s){add(l,s);add(r+1,-s);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T[maxm];
int tot;
int fa[maxn],siz[maxn],dep[maxn],dfn[maxn];
int f[maxn][maxm],ff[maxn][maxm],g[maxn][maxm];
vector<int> son[maxn][maxm];
// f[u][i] 表示 u 到根的路径最长链为 i 且 u 不和父亲在同一条链的子树内贡献和，g[u][i] 表示 u 到根的路径最长链为 i 且能到达 u 的子树内贡献和
void dfs1(int u,int ft){dfn[u]=++tot;dep[u]=dep[fa[u]=ft]+1;siz[u]=1;go(u,i)if(t^ft)dfs1(t,u),siz[u]+=siz[t];}
void dfs(int u,int ft){
    dep[u]=dep[ft]+1;
    for(int i=1;i<=dep[u];i++)  f[u][i]=g[u][i]=i*siz[u];
    int sf[dep[u]+1];
    mems(sf,0);
    go(u,_)if(t^ft){
        dfs(t,u);
        for(int i=1;i<=dep[u];i++)  sf[i]+=f[t][i];
    }
    go(u,_)if(t^ft){
        for(int i=1;i<=dep[u];i++)  ff[t][i]=sf[i]-f[t][i],T[i].upd(dfn[t],dfn[t]+siz[t]-1,ff[t][i]);
    }
    go(u,_)if(t^ft){
        for(int i=1;i<=dep[u];i++)  gmx(g[u][i],i+g[t][i+1]+sf[i]-f[t][i]);
    }
    go(u,_)if(t^ft){
        for(int i=1;i<=dep[u];i++){
            for(int v:son[u][i-1]){
                int w=i*(i-1)+g[v][i];
                w+=T[i].que(dfn[v]);
                // int x=v;while(x^u)w+=ff[x][i],x=fa[x];
                gmx(f[u][i],w);
            }
        }
    }
    // printf("u = %d %d\n",u,sf[2]);
    // for(int i=1;i<=dep[u];i++)  printf("%d %d %d\n",i,f[u][i],g[u][i]);
}
void matt(int _cases){
    rebuild();for(int i=1;i<=n;i++)for(int j=0;j<=m;j++)son[i][j].clear();for(int i=1;i<=m;i++)T[i].clear();tot=0;
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    dfs1(1,0);
    for(int i=1;i<=n;i++){
        for(int j=0,u=i;u;j++,u=fa[u])  son[u][j].eb(i);
    }
    dfs(1,0);
    printf("%d\n",g[1][1]);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}