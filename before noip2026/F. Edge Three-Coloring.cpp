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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=3020;
bool mem1;
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    pii E[maxn];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
int fa[maxn];
bool vis[maxn],in[maxn];
vector<int> v;
void dfs(int u,int ft){
    vis[u]=true;in[u]=true;
    go(u,i)if(t^ft){
        if(vis[t]){
            if(in[t]){
                if(E[w].fi^u)   swap(E[w].fi,E[w].se);
                v.eb(w);
            }
        }
        else{
            fa[t]=w;dfs(t,u);
        }
    }
    in[u]=false;
}
bool mem2;
void matt(int _cases){
    rebuild();fll(vis,0,n);v.clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v,i);E[i]=pii(u,v);}
    dfs(1,0);assert(v.size()<=10);
    for(int s=1;s<(1<<v.size());s++){
        for(int j=0;j<v.size();j++)if(s&(1<<j)){
            int u=E[v[j]].fi,fr=E[v[j]].se;
            in[v[j]]=1;
            while(u^fr) in[fa[u]]^=1,u=E[fa[u]].fi^E[fa[u]].se^u;
        }
        U.init();
        for(int i=1;i<=m;i++)if(!in[i])U.merge(E[i].fi,E[i].se);else in[i]=false;
        bool fl=true;
        for(int i=1;i<=n;i++)if(U[i]^U[1]){fl=false;break;}
        // for(auto [i,j]:v)    printf("%d %d\n",i,j);
        if(fl)  return puts("YES"),void();
    }
    puts("NO");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}