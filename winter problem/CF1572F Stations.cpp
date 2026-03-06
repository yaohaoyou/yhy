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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2e5+10,inf=1e9;
int n,q;
int a[maxn];
struct BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,ll s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ll query(int l,int r){return l>r?0:que(r)-que(l-1);}
}T[2];
inline void add(int l,int r,int s){T[0].add(l,s);T[0].add(r+1,-s);T[1].add(l,1ll*l*s);T[1].add(r+1,-1ll*(r+1)*s);}
inline ll query(int l,int r){return (r+1)*T[0].query(1,r)-l*T[0].query(1,l-1)-T[1].query(l,r);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int mx[maxn<<2],mxc[maxn<<2],se[maxn<<2],tag[maxn<<2];
    inline void pu(int p){
        mx[p]=max(mx[ls],mx[rs]);
        if(mx[ls]==mx[rs])  se[p]=max(se[ls],se[rs]),mxc[p]=mxc[ls]+mxc[rs];
        else if(mx[ls]>mx[rs])  se[p]=max(se[ls],mx[rs]),mxc[p]=mxc[ls];
        else se[p]=max(mx[ls],se[rs]),mxc[p]=mxc[rs];
    }
    inline void pt(int p,int s){if(mx[p]<=s)return;assert(se[p]<s);mx[p]=s;gmn(tag[p],s);}
    inline void pd(int p){if(tag[p]^inf)pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=inf;}
    void build(setpos){tag[p]=inf;if(l==r)return mx[p]=l,mxc[p]=1,se[p]=-inf,void();setmid;build(lson);build(rson);pu(p);}
    void upd(setpos,int pl,int pr,int s){
        if(mx[p]<=s)    return;
        if(l^r)pd(p);setmid;
        if(l>=pl&&r<=pr){
            if(se[p]<s) return add(s+1,mx[p],-mxc[p]),pt(p,s);
            upd(lson,pl,pr,s);upd(rson,pl,pr,s);pu(p);
            return;
        }
        if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);
    }
    inline void upd(int x,int s){
        int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}
        add(x,mx[p],-1);mx[p]=s;add(x,mx[p],1);
        while(p>>=1)pu(p);
    }
    void print(setpos){if(l==r)return;pd(p);setmid;print(lson);print(rson);pu(p);}
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   add(i,i,1);
    build(all);
    while(q--){
        int op,l,r;scanf("%d%d%d",&op,&l,&r);
        if(op==1){
            if(l^1) upd(all,1,l-1,l-1);
            upd(l,r);
        }
        else{
            printf("%lld\n",query(l,r));
        }
    }
}