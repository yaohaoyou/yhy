#include<bits/stdc++.h>
#define db double
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pdi pair<db,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e5+10;
const db lim=log(1e9);
int n,q;
int a[maxn];
struct ope{
    int l,r;db x;
    ope(int _l=0,int _r=0,db _x=0){l=_l;r=_r;x=_x;}
};
vector<ope> I[maxn],E[maxn];
db p[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
struct tree{
    pdi mn,se;
    tree operator+(const tree &y){
        tree res;
        res.mn=min(mn,y.mn);
        if(mn.se^res.mn.se) res.se=min(mn,y.se);
        else if(y.mn.se^res.mn.se)  res.se=min(y.mn,se);
        else    res.se=min(se,y.se);
        assert(res.mn.se^res.se.se);
        return res;
    }
    void operator+=(const db &x){mn.fi+=x;se.fi+=x;}
};
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    tree tr[maxn<<2];
    db tag[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int p,db s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos,int k){tag[p]=0;if(l==r)return tr[p]=(tree){pdi(::p[l]*k,U[l]),pdi(1e9,0)},void();setmid;build(lson,k);build(rson,k);pu(p);}
    tree query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid;tree res=(tree){pdi(1e9,0),pdi(1e9,-1)};if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=res+query(rson,pl,pr);return res;}
    void upd(setpos,int pl,int pr,db w){if(l>=pl&&r<=pr)return pt(p,w);setmid;pd(p);if(pl<=mid)upd(lson,pl,pr,w);if(pr>mid)upd(rson,pl,pr,w);pu(p);}
}
using namespace SegmentTree;
pdi to[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),p[i]=log(a[i]);
    while(q--){
        int l1,r1,l2,r2,w;scanf("%d%d%d%d%d",&l1,&r1,&l2,&r2,&w);
        db ww=log(w);
        I[l1].eb(l2,r2,ww);I[r1+1].eb(l2,r2,-ww);
        I[l2].eb(l1,r1,ww);I[r2+1].eb(l1,r1,-ww);
        E[r1].eb(l2,r2,ww);E[l1-1].eb(l2,r2,-ww);
        E[r2].eb(l1,r1,ww);E[l2-1].eb(l1,r1,-ww);
        int l=max(l1,l2),r=min(r1,r2);
        if(l<=r)    I[l].eb(l,r,-ww),I[r+1].eb(l,r,ww),E[r].eb(l,r,-ww),E[l-1].eb(l,r,ww);
    }
    U.init();
    db ans=0;int edg=0;
    while(edg^(n-1)){
        // debug("edg = %d\n",edg);
        for(int i=1;i<=n;i++)   to[i]=pdi(1e9,1e9);
        build(all,-1);
        for(int i=1;i<=n;i++){
            for(auto [l,r,w]:I[i])  upd(all,l,r,w);
            if(i^1){
                tree x=query(all,1,i-1);
                pdi w=U[i]==x.mn.se?x.se:x.mn;w.fi+=p[i];
                to[U[i]]=min(to[U[i]],w);
            }
        }
        build(all,1);
        for(int i=n;i;i--){
            for(auto [l,r,w]:E[i])  upd(all,l,r,w);
            if(i^n){
                tree x=query(all,i+1,n);
                pdi w=U[i]==x.mn.se?x.se:x.mn;w.fi-=p[i];
                to[U[i]]=min(to[U[i]],w);
            }
        }
        for(int i=1;i<=n;i++)if(U[i]==i&&U[to[i].se]!=i){
            if(to[i].fi>lim)    return puts("1000000000"),0;
            ans+=exp(to[i].fi);
            if(ans>1e9) return puts("1000000000"),0;
            U.merge(to[i].se,i);edg++;
        }
    }
    printf("%.10lf\n",ans);
}