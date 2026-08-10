#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e6+10;
int n,q,tot;
int a[maxn];
piii Q[maxn];
ll ans[maxn];
int dfsn[maxn],siz[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
}U;
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
priority_queue<pli,vector<pli>,greater<pli>> pq;
int fa[maxn];bool del[maxn];
struct BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,ll s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ll query(int l,int r){return que(r)-que(l-1);}
    inline void upd(int x,int y,ll s){if(fa[x])add(dfsn[fa[x]],-s);add(dfsn[y],s);}
    inline ll calc(int u){return query(dfsn[u],dfsn[u]+siz[u]-1);}
}T[2];
void dfs(int u,int ft){
    fa[u]=ft;dfsn[u]=++tot;siz[u]=1;
    T[0].upd(u,u,1);T[1].upd(u,u,a[u]);if(ft)pq.ep(-a[u],u);
    go(u,i){if(t==ft)continue;dfs(t,u);siz[u]+=siz[t];}
}
void slv(int u,int x){
    del[u]=true;
    while(u^1){
        U.merge(u,fa[u]);
        int v=U.find(u);
        T[0].upd(v,fa[u],T[0].calc(u));
        T[1].upd(v,fa[u],T[1].calc(u));
        int sz=T[0].calc(v);ll val=T[1].calc(v);
        if(1ll*sz*x+val>=0)  del[v]=true;
        else{pq.ep((ll)ceil(1.0*-val/sz),v);break;}
        u=v;
    }
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(x,i);}
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=q;i++)   scanf("%d%d",&Q[i].fi.se,&Q[i].fi.fi),Q[i].se=i;
    dfs(1,0);
    sort(Q+1,Q+q+1);
    U.init();
    for(int i=1;i<=q;i++){
        auto [x,uu]=Q[i].fi;
        while(!pq.empty()&&x>=pq.top().fi){
            int u=pq.top().se;pq.pop();
            if(del[u])  continue;
            slv(u,x);
        }
        ans[Q[i].se]=1ll*T[0].calc(uu)*x+T[1].calc(uu);
    }
    for(int i=1;i<=q;i++)   printf("%lld\n",ans[i]);
}