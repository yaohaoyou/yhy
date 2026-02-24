#include<bits/stdc++.h>
#define ll long long
#define ui unsigned int
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e6+10,inf=1e9;
const ll INF=4e18;
bool mem1;
int n,m;ui seed;
int b[maxn];
piii a[maxn];int w[maxn];
inline void gmn(ll &x,ll y){(x>y)&&(x=y);}
inline void gmx(ll &x,ll y){(x<y)&&(x=y);}
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
struct bit{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){x+=2;while(x<=m){gmx(tr[x],s);x+=lowbit(x);}}
    inline int que(int x){x+=2;int res=-inf;while(x){gmx(res,tr[x]);x^=lowbit(x);}return res;}
    void clear(){for(int i=0;i<=m;i++)tr[i]=-inf;}
}T2;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,-1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll tr[maxn<<2],res=INF;
    void query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return res=tr[p],void();setmid;if(pl<=mid&&tr[ls]<res)query(lson,pl,pr);if(pr>mid&&tr[rs]<res)query(rson,pl,pr);}
    inline void upd(int x,ll s){int p=1,l=-1,r=m;while(l^r){gmn(tr[p],s);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}gmn(tr[p],s);}
}
using namespace SegmentTree;
ll dp[maxn];
int mx[maxn];
void discrete(){
    for(int i=1;i<=n;i++)   b[++m]=a[i].fi.fi,b[++m]=a[i].fi.se;
    sort(b+1,b+m+1);m=unique(b+1,b+m+1)-b-1;
    for(int i=1;i<=n;i++)   a[i].fi.fi=lower_bound(b+1,b+m+1,a[i].fi.fi)-b,a[i].fi.se=lower_bound(b+1,b+m+1,a[i].fi.se)-b;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi.fi,&a[i].fi.se),a[i].se=i,w[i]=a[i].fi.se-a[i].fi.fi;
    discrete();
    // for(int i=1;i<=n;i++)   printf("%d %d\n",a[i].fi.fi,a[i].fi.se);
    m+=2;T2.clear();mems(tr,0x3f);
    sort(a+1,a+n+1);
    for(int i=n;i;i--)  mx[i]=max(mx[i+1],a[i].fi.fi);
    upd(-1,0);T2.add(-1,-1);
    ll ans=INF;
    for(int i=1;i<=n;i++){
        int l=a[i].fi.fi,r=a[i].fi.se,id=a[i].se;
        T2.add(r,l);
        if(w[id]>=ans)   continue;
        // printf("%d %d\n",l,r);
        int L=T2.que(l-1);
        res=INF;query(all,L,l-1);
        dp[i]=res+w[id];
        if(dp[i]>=ans)  continue;
        if(mx[i+1]<=r)  gmn(ans,dp[i]);
        upd(r,dp[i]);
    }
    printf("%lld\n",ans);
}