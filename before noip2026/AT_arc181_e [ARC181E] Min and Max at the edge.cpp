#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
bool mem1;
const int maxn=2e5+10,inf=1e9;
int n,m;
const int maxm=maxn<<1;
mt19937_64 matt(time(0));
struct Graph{
    #define GO(o,x,i) for(int i=T[o].head[x],t=T[o].e[i].to,w=T[o].e[i].w;i;i=T[o].e[i].nxt,t=T[o].e[i].to,w=T[o].e[i].w)
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
    int dep[maxn],dfn[maxn],siz[maxn],tot;
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){dep[u]=dep[ft]+1;siz[u]=1;st[0][dfn[u]=++tot]=ft;go(u,i)if(t^ft)dfs(t,u),siz[u]+=siz[t];}
    void build(){
        tot=0;dfs(1,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}T[2];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    piii tr[maxn<<2];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    inline void upd(int x,piii s){int p=1,l=1,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=min(tr[p],s);while(p>>=1)pu(p);}
    piii query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;return pr<=mid?query(lson,pl,pr):pl>mid?query(rson,pl,pr):min(query(lson,pl,pr),query(rson,pl,pr));}
    void clr(){for(int i=0;i<=(n<<2);i++)tr[i]=piii(pii(inf,inf),inf);}
}
using namespace SegmentTree;
bool ans[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
ull base[maxn];
ull hsh;
ull H[2][maxn];
vector<piii> ins[2][maxn],Q[2][maxn];
piii mn[maxn];
set<pii> edg[2];
pii E[maxn],in[maxn];
map<pii,int> mp;
inline pii w(pii x,bool o){
    int u=x.fi,v=x.se;if(u>v)swap(u,v);
    if(!o)  return pii(-u,v);
    else    return pii(v,-u);
}
void kruskal(bool o){
    edg[o].clear();
    sort(E+1,E+m+1,[&](pii x,pii y){return w(x,o)<w(y,o);});
    U.init();
    for(int i=1;i<=m;i++){
        auto [u,v]=E[i];
        if(U[u]==U[v])  continue;
        U.merge(u,v);
        edg[o].ep(u,v);
    }
}
void dfs(int u,int ft,bool o){
    GO(o,u,i)if(t^ft){
        Q[0][T[o].dfn[t]].eb(pii(T[o].dfn[t],T[o].dfn[t]+T[o].siz[t]-1),w);
        Q[1][T[o].dfn[t]+T[o].siz[t]-1].eb(pii(T[o].dfn[t],T[o].dfn[t]+T[o].siz[t]-1),w);
        dfs(t,u,o);
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);E[i]=pii(u,v);in[i]=pii(u,v);assert(!mp.count(in[i]));mp[in[i]]=i;}
    for(int i=1;i<=m;i++)   base[i]=matt();
    for(bool o:{0,1}){
        kruskal(o);
        // for(auto [u,v]:edg[o])  printf("%d\n",mp[pii(u,v)]);puts("");
        // for(pii i:edg[o])   printf("%d %d\n",i.fi,i.se);puts("");
        hsh=0;
        for(int i=1;i<=m;i++)if(edg[o].find(in[i])!=edg[o].end())T[o].adde(in[i].fi,in[i].se,i),hsh+=base[i];
        for(int i=1;i<=n;i++)   ins[0][i].clear(),ins[1][i].clear(),Q[0][i].clear(),Q[1][i].clear();
        T[o].build();dfs(1,0,o);
        for(int i=1;i<=m;i++){
            auto [u,v]=in[i];
            if(edg[o].find(in[i])==edg[o].end()){
                int l=T[o].dfn[u],r=T[o].dfn[v];
                if(l>r)swap(l,r);
                ins[0][l].eb(in[i],r);ins[1][r].eb(in[i],l);
                H[o][i]=hsh;
            }
            else    H[o][i]=hsh-base[i];
        }
        for(int i=1;i<=m;i++)   mn[i]=piii(pii(inf,inf),inf);
        clr();
        for(int i=1;i<=n;i++){
            for(piii j:Q[0][i]) mn[j.se]=min(mn[j.se],query(all,j.fi.fi,j.fi.se));
            for(piii j:ins[0][i])   upd(j.se,piii(w(j.fi,o),mp[j.fi]));
            ins[0][i].clear();Q[0][i].clear();
        }
        clr();
        for(int i=n;i;i--){
            for(piii j:Q[1][i]) mn[j.se]=min(mn[j.se],query(all,j.fi.fi,j.fi.se));
            for(piii j:ins[1][i])   upd(j.se,piii(w(j.fi,o),mp[j.fi]));
            ins[1][i].clear();Q[1][i].clear();
        }
        // printf("%d %d %d\n",mn[34567].fi.fi,mn[34567].fi.se,mn[34567].se);
        for(int i=1;i<=m;i++)if(edg[o].find(in[i])!=edg[o].end()){
            if(mn[i].se<=m) H[o][i]+=base[mn[i].se];
            else    H[o][i]=matt();
        }
        // printf("%llu\n",hsh);
    }
    for(int i=1;i<=m;i++)   puts(H[0][i]==H[1][i]?"Yes":"No");
}