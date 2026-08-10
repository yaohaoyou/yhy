#include<bits/stdc++.h>
#include"teleport.h"
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=5e5+10,maxm=1e6+10;
const ll INF=1e18;
int n,q;
vector<pii> Q[maxn];
struct frac{
    ll p;int q;
    frac(ll x=0,int y=1){int g=__gcd(x,1ll*y);p=x/g;q=y/g;}
    inline bool operator<(frac y){return __int128(p)*y.q<__int128(y.p)*q;}
    inline bool operator>(frac y){return __int128(p)*y.q>__int128(y.p)*q;}
    inline bool operator==(frac y){return p==y.p&&q==y.q;}
    inline bool operator<=(frac y){return *this==y||*this<y;}
};
vector<pli> ans;
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
vector<int> son[maxn];
int siz[maxn];
int dep[maxn],s[maxn],dfn[maxn];
int tot,mxd,all,rt;
namespace stLCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){dep[u]=dep[ft]+1;st[0][dfn[u]=++tot]=ft;go(u,i)if(t^ft)dfs(t,u);}
    void build(){
        dfs(1,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
bool vis[maxn];
struct Vector{
    int siz;
    int _s1[maxn*20];
    ll _sd[maxn*20];
    int l[maxn],r[maxn];
    inline int size(int x){return l[x]?r[x]-l[x]+1:0;}
    inline int& s1(int i,int x){return _s1[l[i]+x];}
    inline ll& sd(int i,int x){return _sd[l[i]+x];}
    inline void resize(int i,int x){if(!l[i])l[i]=++siz;siz=r[i]=l[i]+x-1;}
}vec[2];
int L[maxn],R[maxn],rk[maxn],fa[maxn],p[maxn];
void getWC(int u,int ft){
    siz[u]=1;
    int mx=0;
    go(u,i)if((t^ft)&&!vis[t]){
        getWC(t,u);
        siz[u]+=siz[t];
        gmx(mx,siz[t]);
    }
    gmx(mx,all-siz[u]);
    if(mx<=all/2)   rt=u;
}
void dfs(int u){
    vis[u]=true;
    getWC(u,0);
    go(u,i)if(!vis[t]){
        all=siz[t];getWC(t,u);
        son[u].eb(rt);fa[rt]=u;
        dfs(rt);
    }
}
void dfs1(int u){rk[L[u]=++tot]=u;for(int t:son[u])dfs1(t);R[u]=tot;}
frac mn[maxn];
inline frac calc(int x,int k){
    int u=x,y=x,a=vec[0].s1(u,min(vec[0].size(u)-1,k));ll g=vec[0].sd(u,min(vec[0].size(u)-1,k));
    x=fa[x];
    while(x){
        int di=dis(u,x),d=k-di;
        if(d>=0){
            int sz0=min(vec[0].size(x)-1,d),sz1=min(vec[1].size(y)-1,d);
            ll t=vec[0].s1(x,sz0)-vec[1].s1(y,sz1);
            a+=t;
            g+=vec[0].sd(x,sz0)-vec[1].sd(y,sz1)+t*di;
        }
        y=x;x=fa[x];
    }
    return frac(g+n,a);
}
inline frac MIN(frac x,frac y){return x<y?x:y;}
void dfs2(int u,int ft){
    if(ft){
        frac x=calc(u,p[ft]-1),y=calc(u,p[ft]),z=calc(u,p[ft]+1);
        if(x<MIN(y,z))  mn[u]=x,p[u]=p[ft]-1;
        else if(z<MIN(x,y)) mn[u]=z,p[u]=p[ft]+1;
        else    mn[u]=y,p[u]=p[ft];
    }
    go(u,i)if(t^ft)dfs2(t,u);
}
vector<pli> teleport(int c,int N,int M,vector<int> u,vector<int> v,vector<int> x,vector<int> y){
    n=N;q=M;ans.resize(q);
    for(int i=1;i<n;i++)    adde(u[i-1]+1,v[i-1]+1);
    stLCA::build();
    {all=n;getWC(1,0);int RT=rt;dfs(rt);rt=RT;}
    tot=0;dfs1(rt);
    for(int u=1;u<=n;u++){
        for(int i=L[u];i<=R[u];i++){
            int d=dis(u,rk[i]);
            if(vec[0].size(u)<=d)   vec[0].resize(u,d+1);
            vec[0].s1(u,d)++;vec[0].sd(u,d)+=d;
        }
        for(int i=vec[0].l[u]+1;i<=vec[0].r[u];i++) vec[0]._s1[i]+=vec[0]._s1[i-1],vec[0]._sd[i]+=vec[0]._sd[i-1];
        if(fa[u]){
            for(int i=L[u];i<=R[u];i++){
                int d=dis(fa[u],rk[i]);
                if(vec[1].size(u)<=d)   vec[1].resize(u,d+1);
                vec[1].s1(u,d)++;vec[1].sd(u,d)+=d;
            }
            for(int i=vec[1].l[u]+1;i<=vec[1].r[u];i++) vec[1]._s1[i]+=vec[1]._s1[i-1],vec[1]._sd[i]+=vec[1]._sd[i-1];
        }
    }
    for(int i=0;i<q;i++)    Q[y[i]+1].eb(x[i]+1,i);
    {
        int l=0,r=0,u=1;
        {int x=u;while(x)gmx(r,vec[0].size(x)-1+dis(u,x)),x=fa[x];}
        while(l<=r){
            int mid=(l+r)>>1;
            frac x=calc(u,mid),y=calc(u,mid+1);
            if(x<=y) r=mid-1,mn[u]=x,p[u]=mid;
            else    l=mid+1;
        }
    }
    dfs2(1,0);
    for(int u=1;u<=n;u++){
        if(Q[u].empty())    continue;
        for(auto [s,id]:Q[u])ans[id]=mn[u]<frac(dis(s,u))?pli(mn[u].p,mn[u].q):pli(dis(s,u),1);
    }
    return ans;
}
signed main() {
    int c, n, m;
    std::cin >> c >> n >> m;

    std::vector<int> u(n), v(n), x(m), y(m);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> u[i] >> v[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> x[i] >> y[i];
    }

    std::vector<std::pair<long long, int>> a = teleport(c, n, m, u, v, x, y);

    if (static_cast<int>(a.size()) != m) {
        std::cout << "The length of a and b is not m.\n";
        return 0;
    }

    for (int i = 0; i < m; i++) {
        std::cout << a[i].first << ' ' << a[i].second << '\n';
    }
    return 0;
}