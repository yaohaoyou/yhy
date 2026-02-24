#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10,maxm=2e5+10,maxV=maxn+maxm;
bool mem1;
int n,m,q,V;
int a[maxn],b[maxV];
ll ans[maxm];
vector<int> son[maxn];
map<pii,int> G;
pii E[maxm];
piii Q[maxm];
vector<int> v[maxm];
int tot;
int low[maxn],dfsn[maxn],bel[maxn],id[maxm];
bool instk[maxn];
stack<int> stk;
int rt[maxn];
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all(x) rt[x],1,V
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    queue<int> clr;
    int cur;
    ll tr[maxV*20];
    int lc[maxV*20],rc[maxV*20],siz[maxV*20];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];siz[p]=siz[ls]+siz[rs];}
    inline int nd(){int p;if(!clr.empty())p=clr.front();else p=++cur;tr[p]=lc[p]=rc[p]=siz[p]=0;return p;}
    int merge(int p,int q,int l,int r){
        if(!p||!q)  return p|q;
        if(l==r)    return tr[p]+=tr[q],siz[p]+=siz[q],p;
        setmid;
        lc[p]=merge(lc[p],lc[q],l,mid);rc[p]=merge(rc[p],rc[q],mid+1,r);pu(p);
        return p;
    }
    ll binary(setpos,int k){if(!p)return 0;if(l==r) return 1ll*min(siz[p],k)*b[l];setmid;if(siz[rs]>=k)return binary(rson,k);return tr[rs]+binary(lson,k-siz[rs]);}
    inline void upd(setpos,int x,int s,int o){if(!p)p=nd();if(l==r)return tr[p]+=s,siz[p]+=o,void();setmid;(x<=mid)?upd(lson,x,s,o):upd(rson,x,s,o);pu(p);}
}
using namespace SegmentTree;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
}U;
bool mem2;
void tarjan(int u){
    low[u]=dfsn[u]=++tot;stk.ep(u);instk[u]=true;
    for(int t:son[u]){
        if(!dfsn[t]) tarjan(t),low[u]=min(low[u],low[t]);
        else if(instk[t])   low[u]=min(low[u],dfsn[t]);   
    }
    if(low[u]==dfsn[u]){
        int p;
        do{p=stk.top();instk[p]=false;stk.pop();bel[p]=u;}while(p^u);
    }
}
void divide(int l,int r,vector<piii> edg){
    if(l==r)    return;
    int mid=(l+r)>>1;
    vector<piii> em,el,er;em.clear();el.clear();er.clear();
    for(piii i:edg)if(id[i.fi]<=mid)em.eb(i);
    vector<int> tmp;tmp.clear();
    for(piii i:em){int u=i.se.fi,v=i.se.se;son[u].eb(v);tmp.eb(u);tmp.eb(v);}
    for(int u:tmp)if(!dfsn[u])tarjan(u);
    for(piii i:edg)if(id[i.fi]>mid){
        int &u=i.se.fi,&v=i.se.se;
        if(bel[u]&&bel[u]==bel[v]){id[i.fi]=q+1;continue;}
        u=bel[u]?bel[u]:u;v=bel[v]?bel[v]:v;
        er.eb(i);
    }
    for(piii i:em){
        int u=i.se.fi,v=i.se.se;
        if(bel[u]&&bel[u]==bel[v])  el.eb(i);
        else    id[i.fi]=mid+1,er.eb(i.fi,pii(bel[u],bel[v]));
    }
    for(int u:tmp)son[u].clear(),bel[u]=dfsn[u]=low[u]=0;tot=0;assert(stk.empty());
    divide(l,mid,el);divide(mid+1,r,er);
}
void discrete(){
    sort(b+1,b+V+1);V=unique(b+1,b+V+1)-b-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(b+1,b+V+1,a[i])-b;
}
main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),b[++V]=a[i];
    for(int i=1;i<=m;i++)   scanf("%d%d",&E[i].fi,&E[i].se),G[pii(E[i].fi,E[i].se)]=i;
    vector<piii> vec;vec.clear();
    for(int i=1;i<=q;i++){
        int op,u,v;
        scanf("%d%d%d",&op,&u,&v);
        if(op==1)  id[G[pii(u,v)]]=q-i+1;
        if(op==2)   a[u]+=v,b[++V]=a[u];
        Q[i]=piii(op,pii(u,v));
    }
    discrete();
    vec.clear();for(int i=1;i<=m;i++)   vec.eb(i,E[i]);
    divide(0,q+1,vec);
    for(int i=1;i<=m;i++)   v[id[i]].eb(i);
    for(int i=1;i<=n;i++)   upd(all(i),a[i],b[a[i]],1);
    U.init();
    mems(ans,-1);
    for(int i=0;i<=q;i++){
        for(int j:v[i]){
            int u=E[j].fi,v=E[j].se;
            u=U.find(u);v=U.find(v);
            if(u==v)    continue;
            U.merge(v,u);
            rt[u]=merge(rt[u],rt[v],1,V);rt[v]=0;
        }
        if(Q[q-i+1].fi==2){
            int u=Q[q-i+1].se.fi,val=Q[q-i+1].se.se,x=U.find(u);
            upd(all(x),a[u],-b[a[u]],-1);
            a[u]=b[a[u]];a[u]-=val;a[u]=lower_bound(b+1,b+V+1,a[u])-b;
            upd(all(x),a[u],b[a[u]],1);
        }
        if(Q[q-i+1].fi==3){
            int u=U.find(Q[q-i+1].se.fi),k=Q[q-i+1].se.se;
            ans[q-i+1]=binary(all(u),k);
        }
    }
    for(int i=1;i<=q;i++)if(~ans[i])printf("%lld\n",ans[i]);
}