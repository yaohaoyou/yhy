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
const int maxn=3e5+10;
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
inline void gmx(int &x,int y){(x<y)&&(x=y);}
int dfsn[maxn],siz[maxn],fa[maxn];int tot;
vector<int> pa[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
}U;
namespace st{
    int st[20][maxn],Log[maxn];
    inline int mindfn(int x,int y){return dfsn[x]<dfsn[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfsn[x])>(y=dfsn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using st::LCA;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int query(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline void upd(int l,int r,int s){add(l,s);add(r+1,-s);}
}T;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void upd(int x,int s){int p=1,l=1,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}gmx(tr[p],s);while(p>>=1)pu(p);}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)gmx(res,query(rson,pl,pr));return res;}
}
using namespace SegmentTree;
void dfs(int u,int ft){
    siz[u]=1;st::st[0][dfsn[u]=++tot]=fa[u]=ft;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
        siz[u]+=siz[t];
    }
}
int f[maxn],g[maxn],sum[maxn],del[maxn],b[maxn];
pii a[maxn];
inline int p(int x,int y){int l=LCA(x,y);return 1+sum[l]-T.query(dfsn[x])-T.query(dfsn[y]);}
void dfs1(int u,int ft){
    go(u,i){
        if(t==ft)   continue;
        dfs1(t,u);
        sum[u]+=f[t];
    }
    f[u]=sum[u];
    for(int i:pa[u])   gmx(f[u],b[i]=p(a[i].fi,a[i].se));
    T.upd(dfsn[u],dfsn[u]+siz[u]-1,del[u]=f[u]-sum[u]);
}
void dfs2(int u,int ft){
    sort(pa[u].begin(),pa[u].end(),[&](int x,int y){return b[x]>b[y];});
    go(u,i){
        if(t==ft)   continue;
        g[t]=g[u]+sum[u];
        for(int j:pa[u]){
            int x=dfsn[a[j].fi],y=dfsn[a[j].se];
            if(x>=dfsn[t]&&x<=dfsn[t]+siz[t]-1) continue;
            if(y>=dfsn[t]&&y<=dfsn[t]+siz[t]-1) continue;
            gmx(g[t],g[u]+b[j]);
            break;
        }
        if(dfsn[u]<dfsn[t])gmx(g[t],query(all,dfsn[u],dfsn[t]-1));
        if(dfsn[t]+siz[t]<dfsn[u]+siz[u])gmx(g[t],query(all,dfsn[t]+siz[t],dfsn[u]+siz[u]-1));
        // dfsn[u],dfsn[t],dfsn[t]+siz[t]-1,dfsn[u]+siz[u]-1;
        g[t]-=f[t];
    }
    for(int i:pa[u])   upd(dfsn[a[i].fi],g[u]+b[i]),upd(dfsn[a[i].se],g[u]+b[i]);
    go(u,i)if(t^ft)dfs2(t,u);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    srand(time(0));
    int rt=rand()%(n-1)+1;
    dfs(rt,0);st::build();
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        pa[LCA(x,y)].eb(i);a[i]=pii(x,y);
    }
    dfs1(rt,0);dfs2(rt,0);
    U.init();
    for(int i=1;i<=n;i++){
        if(g[i]+sum[i]!=f[rt])   continue;
        go(i,j)if(g[t]+sum[t]==f[rt])   U.merge(i,t);
    }
    mems(siz,0);
    for(int i=1;i<=n;i++)if(g[i]+sum[i]==f[rt])siz[U.find(i)]++;
    ll ans=0;
    for(int i=1;i<=n;i++)   ans+=1ll*siz[i]*siz[i];
    printf("%lld\n",ans);
}