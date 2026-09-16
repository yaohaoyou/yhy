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
bool mem1;
const int maxn=2e5+10;
int n,m;
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
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
set<pii> edg[2];
pii E[maxn];
inline pii w(pii x,bool o){
    int u=x.fi,v=x.se;if(u>v)swap(u,v);
    if(!o)  return pii(-u,v);
    else    return pii(-v,u);
}
void kruskal(bool o){
    sort(E+1,E+m+1,[&](pii x,pii y){return w(x,o)<w(y,o);});
    U.init();
    for(int i=1;i<=m;i++){
        auto [u,v]=E[i];
        if(U[u]==U[v])  continue;
        U.merge(u,v);
        edg[o].ep(u,v);
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);E[i]=pii(u,v);}
    kruskal(0);
    kruskal(1);
    for(pii i:edg[0])   printf("%d %d\n",i.fi,i.se);
    int cnt=0;for(pii i:edg[0])if(edg[1].find(i)==edg[1].end())cnt++;
    if(cnt>1){
        for(int i=1;i<=m;i++)   puts("No");
        return 0;
    }
}