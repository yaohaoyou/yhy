#include<bits/stdc++.h>
#define db double
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
const int maxn=2e5+10;
const ll INF=4e18;
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;ll w;}e[maxm];
    inline void add(int u,int v,ll w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,ll w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
int n,m;
int P[maxn];ll lim[maxn],Q[maxn];
int a[maxn],dfsn[maxn],tot,fa[20][maxn];
ll dep[maxn];
ll dp[maxn];
struct line{ll k,b;}L[maxn];
inline bool cmp(int u,int v,int x){return L[u].k*x+L[u].b<=L[v].k*x+L[v].b;}
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all(x) root[x],1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    int cur,root[maxn<<2];
    int tr[maxn*20],lc[maxn*20],rc[maxn*20];
    void upd(setpos,int u){
        if(!p)  p=++cur;
        setmid,&v=tr[p];
        if(!v)  return v=u,void();
        if(cmp(u,v,a[mid])) swap(u,v);
        if(l==r)return;
        if(cmp(u,v,a[l]))   upd(lson,u);
        if(cmp(u,v,a[r]))   upd(rson,u);
    }
    inline ll query(int x,int y,int c){
        int p=root[c],l=1,r=m;ll ret=INF;
        while(l^r){
            if(x)
            if(!p)  return ret;
            if(tr[p])ret=min(ret,L[tr[p]].k*y+L[tr[p]].b);
            setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);
        }
        if(p&&tr[p])ret=min(ret,L[tr[p]].k*y+L[tr[p]].b);
        return ret;
    }
    inline void update(int x,int id){
        int p=1,l=1,r=n;
        while(l^r){upd(all(p),id);setmid;(x<=mid)?(p<<=1,r=mid):(p=p<<1|1,l=mid+1);}
        upd(all(p),id);
    }
    ll query(int p,int l,int r,int pl,int pr,int x,int y){
        if(l>=pl&&r<=pr)return query(x,y,p);
        setmid;ll res=INF;if(pl<=mid)res=query(p<<1,l,mid,pl,pr,x,y);if(pr>mid)res=min(res,query(p<<1|1,mid+1,r,pl,pr,x,y));return res;
    }
}
using namespace SegmentTree;
void discrete(){
    memc(a,P);sort(a+1,a+n+1);m=unique(a+1,a+n+1)-a-1;
    for(int i=1;i<=n;i++)   P[i]=lower_bound(a+1,a+m+1,P[i])-a;
}
void dfs(int u,int ft){
    fa[0][u]=ft;
    go(u,i){
        ll w=e[i].w;
        dep[t]=dep[u]+w;
        dfs(t,u);
    }
    dfsn[u]=++tot;
}
void build(){for(int i=1;i<20;i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];}
inline int jump(int x,ll k){for(int i=19;~i;i--)if(dep[x]-dep[fa[i][x]]<=k)k-=(dep[x]-dep[fa[i][x]]),x=fa[i][x];return x;}
void dfs2(int u){
    if(u^1){
        int tp=jump(u,lim[u]);
        dp[u]=query(1,1,n,dfsn[u],dfsn[tp],P[u],a[P[u]])+a[P[u]]*dep[u]+Q[u];
    }
    // printf("%d : %d (%d,%d)\n",u,dfsn[u],-dep[u],dp[u]);
    L[u]={-dep[u],dp[u]};update(dfsn[u],u);
    go(u,i)dfs2(t);
}
int main(){
    scanf("%d%*d",&n);
    for(int i=2;i<=n;i++){
        int f;ll w;scanf("%d%lld%d%lld%lld",&f,&w,&P[i],&Q[i],&lim[i]);
        add(f,i,w);
    }
    dfs(1,1);build();
    discrete();
    dfs2(1);
    for(int i=2;i<=n;i++)   printf("%lld\n",dp[i]);
}