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
inline void gmn(auto &x,auto y){if(x>y)x=y;}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e5+10;
bool mem1;
int n,m;
int a[maxn];
pii d[maxn],c[maxn];
pii b[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);copy_n(c,n+1,d);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){x=find(x);y=find(y);fa[x]=y;gmn(d[y],d[x]);}
    inline int operator[](int x){return find(x);}
}U;
namespace Graph{
    const int maxm=4e5+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
vector<int> out;
bool vis[maxn],in[maxm];
vector<int> v[maxn];
void dfs(int u,int fr){
    vis[u]=true;
    go(u,i)if((w^fr)&&U[u]==U[t]){
        if(!in[w]){
            out.eb(w);in[w]=true;
            gmn(b[u].fi,b[t].fi);gmn(b[t].fi,b[u].fi);
        }
        if(!vis[t])dfs(t,w);
    }
}
bool mem2;
void matt(int _cases){
    rebuild();out.clear();fill_n(vis,n+1,0);fill_n(in,m+1,0);
    for(int i=0;i<=n;i++)v[i].clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),c[i]=b[i]=pii(a[i],i);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);if(a[u]^a[v]){adde(u,v,i);gmn(c[u],b[v]);gmn(c[v],b[u]);}else out.eb(i),in[i]=true;}
    U.init();
    sort(b+1,b+n+1,greater<pii>());
    for(int _=1;_<=n;_++){
        int u=b[_].se;
        go(u,i)if((U[t]^U[u])&&a[t]>=a[u]){
            int x=U[u],y=U[t];
            if(d[y].fi<a[u])   U.merge(x,y);
        }
    }
    sort(b+1,b+n+1,[&](pii x,pii y){return x.se<y.se;});
    ll ans=0;
    for(int i=1;i<=n;i++)ans+=a[i]-d[U[i]].fi,v[U[i]].eb(i);
    vector<pii> vec;
    for(int i=1;i<=n;i++)if(U[i]==i)vec.eb(d[i].fi,i);
    sort(vec.begin(),vec.end(),greater<pii>());
    for(auto [x,i]:vec){
        for(int j:v[i]){
            go(j,_)if(U[t]!=i&&!in[w])out.eb(w),gmn(b[j].fi,b[t].fi),gmn(b[t].fi,b[j].fi),in[w]=true;
        }
        if(U[d[i].se]==i)dfs(d[i].se,0);
        else{
            for(int j:v[i])if(c[j].se==d[i].se){
                go(j,_)if(t==d[i].se){dfs(j,0);break;}
                break;
            }
        }
    }
    // for(int i=1;i<=n;i++)assert(b[i].fi==d[U[i]].fi);
    // for(int u=1;u<=n;u++)go(u,i)if(!in[w])in[w]=true,out.eb(w),printf("%d %d %d %d | %d %d\n",u,t,d[U[u]].fi,d[U[t]].fi,a[u],a[t]),assert(d[U[u]].fi==d[U[t]].fi);
    printf("%lld\n",ans);
    debug("%d %d\n",out.size(),m);
    assert(out.size()==m);
    for(int i:out)printf("%d ",i);puts("");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}