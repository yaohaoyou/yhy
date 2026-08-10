#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10;
const ll INF=4e18;
int n,q;
int a[maxn];
inline void getmx(ll &x,ll y){(x<y)&&(x=y);}
inline void getmn(ll &x,ll y){(x>y)&&(x=y);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define pos p,l,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll sum[maxn<<2],mxt[maxn<<2],mnt[maxn<<2],tag[maxn<<2];
    int mxc[maxn<<2],mnc[maxn<<2];
    pll mx[maxn<<2],mn[maxn<<2];
    inline void pu(int p){
        sum[p]=sum[ls]+sum[rs];
        mx[p].fi=max(mx[ls].fi,mx[rs].fi);
        if(mx[ls].fi^mx[rs].fi)mx[p].se=(mx[p].fi==mx[ls].fi)?max(mx[ls].se,mx[rs].fi):max(mx[ls].fi,mx[rs].se);
        else    mx[p].se=max(mx[ls].se,mx[rs].se);
        mn[p].fi=min(mn[ls].fi,mn[rs].fi);
        if(mn[ls].fi^mn[rs].fi)mn[p].se=(mn[p].fi==mn[ls].fi)?min(mn[ls].se,mn[rs].fi):min(mn[ls].fi,mn[rs].se);
        else    mn[p].se=min(mn[ls].se,mn[rs].se);
        mxc[p]=(mx[p].fi==mx[ls].fi)*mxc[ls]+(mx[p].fi==mx[rs].fi)*mxc[rs];
        mnc[p]=(mn[p].fi==mn[ls].fi)*mnc[ls]+(mn[p].fi==mn[rs].fi)*mnc[rs];
    }
    inline void ptadd(setpos,ll s){
        tag[p]+=s;mx[p].fi+=s;mx[p].se+=s;mn[p].fi+=s;mn[p].se+=s;sum[p]+=s*(r-l+1);
        if(mxt[p]^INF)mxt[p]+=s;if(mnt[p]+INF)mnt[p]+=s;
    }
    inline void ptmin(int p,ll s){
        if(mn[p].fi>=s)  return;
        getmx(mnt[p],s);getmx(mxt[p],s);
        ll del=s-mn[p].fi;
        sum[p]+=mnc[p]*del;
        if(mx[p].se==mn[p].fi)  mx[p].se=s;
        mn[p].fi=s;getmx(mx[p].fi,mn[p].fi);
        if(mx[p].fi==mx[p].se)  mx[p].se=-INF;
    }
    inline void ptmax(int p,ll s){
        if(mx[p].fi<=s) return;
        ll del=mx[p].fi-s;
        sum[p]-=mxc[p]*del;
        if(mn[p].se==mx[p].fi)  mn[p].se=s;
        mx[p].fi=s;getmn(mn[p].fi,mx[p].fi);
        if(mn[p].fi==mn[p].se)  mn[p].se=INF;
    }
    inline void pd(setpos){
        if(tag[p]){setmid;ptadd(lson,tag[p]);ptadd(rson,tag[p]);tag[p]=0;}
        if(mnt[p]+INF){ptmin(ls,mnt[p]);ptmin(rs,mnt[p]);mnt[p]=-INF;}
        if(mxt[p]^INF){ptmax(ls,mxt[p]);ptmax(rs,mxt[p]);mxt[p]=INF;}
    }
    void build(setpos){
        mxt[p]=INF;mnt[p]=-INF;
        if(l==r){sum[p]=mx[p].fi=mn[p].fi=a[l];mxc[p]=mnc[p]=1;mx[p].se=-INF;mn[p].se=INF;return;}
        setmid;build(lson);build(rson);pu(p);
    }
    void updadd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return ptadd(pos,s);pd(pos);setmid;if(pl<=mid)updadd(lson,pl,pr,s);if(pr>mid)updadd(rson,pl,pr,s);pu(p);}
    void updmin(setpos,int pl,int pr,int s){
        if(mn[p].fi>=s) return;
        if(l>=pl&&r<=pr&&mn[p].se>s)    return ptmin(p,s);
        pd(pos);setmid;
        if(pl<=mid)updmin(lson,pl,pr,s);if(pr>mid)updmin(rson,pl,pr,s);pu(p);
    }
    void updmax(setpos,int pl,int pr,int s){
        if(mx[p].fi<=s) return;
        if(l>=pl&&r<=pr&&mx[p].se<s)   return ptmax(p,s);
        pd(pos);setmid;
        if(pl<=mid)updmax(lson,pl,pr,s);if(pr>mid)updmax(rson,pl,pr,s);pu(p);
    }
    ll query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return sum[p];pd(pos);setmid;ll res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res+=query(rson,pl,pr);return res;}
    ll querymx(setpos,int pl,int pr){if(l>=pl&&r<=pr)return mx[p].fi;pd(pos);setmid;ll res=-INF;if(pl<=mid)res=querymx(lson,pl,pr);if(pr>mid)getmx(res,querymx(rson,pl,pr));return res;}
    ll querymn(setpos,int pl,int pr){if(l>=pl&&r<=pr)return mn[p].fi;pd(pos);setmid;ll res=INF;if(pl<=mid)res=querymn(lson,pl,pr);if(pr>mid)getmn(res,querymn(rson,pl,pr));return res;}
}
using namespace SegmentTree;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build(all);
    scanf("%d",&q);
    while(q--){
        int op,l,r,x;scanf("%d%d%d",&op,&l,&r);
        if(op==1){scanf("%d",&x);updadd(all,l,r,x);}
        if(op==2){scanf("%d",&x);updmin(all,l,r,x);}
        if(op==3){scanf("%d",&x);updmax(all,l,r,x);}
        if(op==4)   printf("%lld\n",query(all,l,r));
        if(op==5)   printf("%lld\n",querymx(all,l,r));
        if(op==6)   printf("%lld\n",querymn(all,l,r));
    }
}