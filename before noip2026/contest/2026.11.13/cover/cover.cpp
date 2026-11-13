#include<bits/stdc++.h>
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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n,m,k;
int a[maxn];
int fa[maxn],lf[maxn],L[maxn],R[maxn];
ll siz[maxn],sz[maxn],f[maxn],w[maxn],ww[maxn];
set<int> st;
bool vis[maxn];
ll ans[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll tr[maxn<<2],tag[maxn<<2];int pos[maxn];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void pt(int p,ll s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void upd(setpos,int pl,int pr,ll s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    inline int bry(){
        int p=1,l=1,r=m;
        while(l^r){
            pd(p);
            int mid=(l+r)>>1;
            if(tr[ls]==tr[p])   p=ls,r=mid;
            else    p=rs,l=mid+1;
        }
        return l;
    }
    inline void upd(int x){int p=pos[x];tr[p]=w[x];while(p>>=1)pu(p);}
    ll Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid;ll res=0;if(pl<=mid)res=Q(lson,pl,pr);if(pr>mid)gmx(res,Q(rson,pl,pr));return res;}
    void build(setpos){tag[p]=0;if(l==r)return pos[l]=p,tr[p]=w[l],void();setmid;build(lson);build(rson);pu(p);}
    int bry(setpos,int pl,int pr){
        if(l==r)    return l;
        setmid;
        if(l>=pl&&r<=pr)return tr[ls]==tr[p]?bry(lson,pl,pr):bry(rson,pl,pr);
        int res=0;
        if(pl<=mid)res=bry(lson,pl,pr);
        if(pr>mid){int t=bry(rson,pl,pr);if(!res||w[res]<w[t])res=t;}
        return res;
    }
}
using namespace SegmentTree;
ll sum;
multiset<ll> s0,s1;
void dfs(int u,int ft){
    bool son=false;
    go(u,i)if(t^ft){son=true;break;}
    L[u]=m+1;
    if(!son)    lf[++m]=u;
    siz[u]=a[u];
    fa[u]=ft;
    go(u,i)if(t^ft){
        dfs(t,u);
        siz[u]+=siz[t];
        sz[u]+=sz[t];
    }
    sz[u]+=siz[u];
    R[u]=m;
}
bool chk(int l,int r){
    if(l>r)return false;
    auto it=st.lower_bound(l);
    return (it!=st.end()&&*it<=r);
}
void dfs2(int u,int ft){
    // printf("%d %d\n",u,ft);
    int p=0,q=0;ll wp,wq;
    if(ft){
        sz[u]=sz[ft]-siz[u]-siz[u]+siz[ft];
        p=bry(all,L[u],R[u]);wp=w[p];
        w[p]-=siz[u];

        q=0;if(L[u]^1)q=bry(all,1,L[u]-1);
        if(R[u]^m){int t=bry(all,R[u]+1,m);if(!q||w[t]>w[q])q=t;}
        wq=w[q];
        w[q]+=siz[ft]-siz[u];
        if(s0.find(wp)!=s0.end())s0.erase(s0.find(wp)),s0.ep(w[p]);
        else    s1.erase(s1.find(wp)),s1.ep(w[p]),sum+=w[p]-wp;
        if(s0.find(wq)!=s0.end())s0.erase(s0.find(wq)),s0.ep(w[q]);
        else    s1.erase(s1.find(wq)),s1.ep(w[q]),sum+=w[q]-wq;
        while(!s0.empty()&&!s1.empty()&&*s0.rbegin()>*s1.begin()){
            ll x=*s0.rbegin(),y=*s1.begin();
            s0.erase(s0.find(x));s1.erase(s1.find(y));
            sum+=x-y;
            s0.ep(y);s1.ep(x);
        }
        upd(p);upd(q);
        siz[u]=siz[ft];
        
        // f[u]=0;memc(ww,w);sort(ww+1,ww+m+1,greater<ll>());
        // assert(Q(all,L[u],R[u])==w[p]);assert(max(L[u]==1?0:Q(all,1,L[u]-1),R[u]==m?0:Q(all,R[u]+1,m))==w[q]);
        // for(int i=1;i<=k;i++)f[u]+=ww[i];
        f[u]=sum;
        // printf("%d : %d %d %d\n",u,sz[u],siz[u],f[u]);
        // for(int i=1;i<=m;i++)   printf("w[%d] = %d\n",lf[i],w[i]);
        ans[u]=sz[u]-siz[u]-f[u];
    }
    go(u,i)if(t^ft)dfs2(t,u);
    if(ft){
        // puts("back");
        if(s0.find(w[p])!=s0.end())s0.erase(s0.find(w[p])),s0.ep(wp);
        else    s1.erase(s1.find(w[p])),s1.ep(wp),sum+=wp-w[p];
        if(s0.find(w[q])!=s0.end())s0.erase(s0.find(w[q])),s0.ep(wq);
        else    s1.erase(s1.find(w[q])),s1.ep(wq),sum+=wq-w[q];
        w[p]=wp;upd(p);
        w[q]=wq;upd(q);
    }
}
bool mem2;
int main(){
    freopen("cover.in","r",stdin);freopen("cover.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    int rt=max_element(deg+1,deg+n+1)-deg;
    dfs(rt,0);
    for(int i=1;i<=n;i++)if(i^rt)upd(all,L[i],R[i],siz[i]);
    for(int i=1;i<=m;i++){
        if (tr[1] == 0) break;
        int u=bry();if(i<=k)f[rt]+=tr[1],st.ep(u);
        w[u]=tr[1];
        u=lf[u];
        while((u^rt)&&!vis[u]){
            upd(all,L[u],R[u],-siz[u]);
            vis[u]=true;
            u=fa[u];
        }
    }
    ans[rt]=sz[rt]-siz[rt]-f[rt];
    if(k>=m){for(int i=1;i<=n;i++)printf("0 ");return 0;}
    build(all);
    memc(ww,w);sort(ww+1,ww+m+1,greater<ll>());
    for(int i=1;i<=m;i++){
        if(i<=k)    s1.ep(ww[i]),sum+=ww[i];
        else    s0.ep(ww[i]);
    }
    // for(int i=1;i<=m;i++)   printf("w[%d] = %d\n",lf[i],w[i]);
    dfs2(rt,0);
    for(int i=1;i<=n;i++)   printf("%lld ",ans[i]);
}