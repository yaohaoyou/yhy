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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10,V=1e9;
int n,m,q;
int a[maxn],b[maxn];
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define al(x) rt[x],1,V
    #define all(x,y) rt[x],rt[y],1,V
    #define ALL 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tot;
    int rt[maxn],cnt[maxn*40],lc[maxn*40],rc[maxn*40];
    ll sum[maxn*40];
    void upd(int &p,int q,int l,int r,int x){
        p=++tot;cnt[p]=cnt[q]+1;sum[p]=sum[q]+x;ls=lc[q];rs=rc[q];
        if(l==r)return;
        setmid;
        (x<=mid)?upd(ls,lc[q],l,mid,x):upd(rs,rc[q],mid+1,r,x);
    }
    int QCNT(setpos,int pl,int pr){if(!p)return 0;if(l>=pl&&r<=pr)return cnt[p];setmid,res=0;if(pl<=mid)res=QCNT(lson,pl,pr);if(pr>mid)res+=QCNT(rson,pl,pr);return res;}
    ll QSUM(setpos,int pl,int pr){if(!p)return 0;if(l>=pl&&r<=pr)return sum[p];setmid;ll res=0;if(pl<=mid)res=QSUM(lson,pl,pr);if(pr>mid)res+=QSUM(rson,pl,pr);return res;}
    int bry(int p,int q,int l,int r,int k){
        if(l==r)    return l;
        setmid;
        if(cnt[rc[q]]-cnt[rs]>=k) return bry(rs,rc[q],mid+1,r,k);
        return bry(ls,lc[q],l,mid,k-(cnt[rc[q]]-cnt[rs]));
    }
    #define setpos int p,int l,int r
    #define ls p<<1
    #define rs p<<1|1
    int tag[maxn<<2];
    ll tr[maxn<<2],S[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int p,int x){tr[p]+=x*S[p];tag[p]+=x;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){tr[p]=tag[p]=S[p]=0;if(l==r)return S[p]=b[l]-b[l-1],void();setmid;build(lson);build(rson);S[p]=S[ls]+S[rs];}
    void U(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pt(p,1);setmid;pd(p);if(pl<=mid)U(lson,pl,pr);if(pr>mid)U(rson,pl,pr);pu(p);}
    ll Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;pd(p);ll res=0;if(pl<=mid)res=Q(lson,pl,pr);if(pr>mid)res+=Q(rson,pl,pr);return res;}
}
using namespace SegmentTree;
ll ans[maxn],s[maxn];
vector<piii> vl[maxn],vr[maxn];
void discrete(){
    memc(b,a);b[n+1]=V;sort(b+1,b+n+2);
    m=unique(b+1,b+n+2)-b-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(b+1,b+m+1,a[i])-b;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),upd(rt[i],rt[i-1],1,V,a[i]),s[i]=s[i-1]+a[i];
    for(int i=1;i<=q;i++){
        int x,y,l,r;scanf("%d%d%d%d",&x,&y,&l,&r);
        if(!x&&!y){ans[i]=s[r]-s[l-1];continue;}
        if(x>=r||y>=n-l+1)  continue;
        int mx=min({bry(all(0,n),x+y),x?bry(all(0,r),x):V,y?bry(all(l-1,n),y):V});
        ans[i]=s[r]-s[l-1]-(QSUM(al(r),mx+1,V)-QSUM(al(l-1),mx+1,V)-1ll*(QCNT(al(r),mx+1,V)-QCNT(al(l-1),mx+1,V))*mx);
        int mn=l-1>=x?bry(all(0,l-1),x)+1:1;
        if(mn<=mx){
            ans[i]-=1ll*(mx-mn+1)*x;
            vl[l-1].eb(pii(mn,mx),i);
        }
        mn=n-r>=y?bry(all(r,n),y)+1:1;
        if(mn<=mx){
            ans[i]-=1ll*(mx-mn+1)*y;
            vr[r+1].eb(pii(mn,mx),i);
        }
    }
    discrete();
    build(ALL);
    for(int i=1;i<=n;i++){
        U(ALL,1,a[i]);
        for(auto [j,id]:vl[i]){
            int l=j.fi,r=j.se,ql=lower_bound(b+1,b+m+1,l)-b+1,qr=upper_bound(b+1,b+m+1,r)-b-1;
            if(ql<=qr)  ans[id]+=Q(ALL,ql,qr);
            if(ql-1>0&&ql-1<=m&&l<=b[ql-1]) ans[id]+=Q(ALL,ql-1,ql-1)/(b[ql-1]-b[ql-2])*(b[ql-1]-l+1);
            if(qr+1<=m&&r>b[qr])    ans[id]+=Q(ALL,qr+1,qr+1)/(b[qr+1]-b[qr])*(r-b[qr]);
        }
    }
    build(ALL);
    for(int i=n;i;i--){
        U(ALL,1,a[i]);
        for(auto [j,id]:vr[i]){
            int l=j.fi,r=j.se,ql=lower_bound(b+1,b+m+1,l)-b+1,qr=upper_bound(b+1,b+m+1,r)-b-1;
            if(ql<=qr)  ans[id]+=Q(ALL,ql,qr);
            if(ql-1>0&&ql-1<=m&&l<=b[ql-1]) ans[id]+=Q(ALL,ql-1,ql-1)/(b[ql-1]-b[ql-2])*(b[ql-1]-l+1);
            if(qr+1<=m&&r>b[qr])    ans[id]+=Q(ALL,qr+1,qr+1)/(b[qr+1]-b[qr])*(r-b[qr]);
        }
    }
    for(int i=1;i<=q;i++)   printf("%lld\n",ans[i]);
}