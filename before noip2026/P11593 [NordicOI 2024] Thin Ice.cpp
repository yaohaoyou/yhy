#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
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
bool mem1;
const int maxn=4e5+10;
int n,m,tot,ee;
int val[maxn],fa[maxn],siz[maxn];
vector<int> a[maxn];
piii E[maxn];
inline int id(int x,int y){return (x-1)*m+y;}
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n*m*2+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
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
bool vis[maxn];
bool chk(int x,int y,int lim){
    if(a[x][y]<lim) return false;
    lim--;
    int u=id(x,y);
    while(u&&lim>0){
        if(vis[u]||val[fa[u]]<lim)  return false;
        vis[u]=true;
        lim-=siz[fa[u]]-siz[u];
        u=fa[u];
    }
    return true;
}
bool check(int x){
    mems(vis,0);
    for(int i=1;i<=m;i++){
        if(chk(1,i,x))return true;
        if(chk(n,i,x))return true;
    }
    for(int i=2;i<n;i++){
        if(chk(i,1,x))return true;
        if(chk(i,m,x))return true;
    }
    return false;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){a[i].resize(m+1);for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);}
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i^n) E[++ee]=piii(pii(id(i,j),id(i+1,j)),min(a[i][j],a[i+1][j]));
            if(j^m) E[++ee]=piii(pii(id(i,j),id(i,j+1)),min(a[i][j],a[i][j+1]));
        }
    }
    sort(E+1,E+ee+1,[&](piii x,piii y){return x.se>y.se;});
    U.init();
    fll(siz,1,n*m);
    tot=n*m;
    for(int i=1;i<=ee;i++){
        int u=E[i].fi.fi,v=E[i].fi.se,w=E[i].se;
        u=U[u];v=U[v];
        if(u==v)    continue;
        val[++tot]=w;U.merge(tot,u);U.merge(tot,v);
        siz[tot]=siz[u]+siz[v];
        fa[u]=fa[v]=tot;add(tot,u);add(tot,v);
    }
    int l=1,r=n*m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,l=mid+1;
        else    r=mid-1;
    }
    printf("%d\n",ans);
}