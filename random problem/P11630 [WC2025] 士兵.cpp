#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
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
const int maxn=5e5+10;
const ll INF=1e18;
int n,m,siz;
int a[maxn],b[maxn],c[maxn],d[maxn<<1],A[maxn];
void discrete(){
    for(int i=1;i<=n;i++)   d[i]=c[i],d[i+n]=a[i];
    d[n<<1|1]=0;
    sort(d+1,d+(n<<1|1)+1);
    siz=unique(d+1,d+(n<<1|1)+1)-d-1;
    for(int i=1;i<=n;i++)   c[i]=lower_bound(d+1,d+siz+1,c[i])-d,A[i]=lower_bound(d+1,d+siz+1,a[i])-d;
}
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,siz
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll tr[maxn<<3],tag[maxn<<3];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void pt(int p,ll s){tag[p]+=s;tr[p]+=s;}
    inline void pd(int p){if(tag[p]){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=0;}}
    inline void mdf(int x,ll s){int p=1,l=1,r=siz;while(l<r){setmid;pd(p);(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=max(tr[p],s);while(p)pu(p>>=1);}
    void build(setpos){tr[p]=-INF;if(l==r)return;setmid;build(lson);build(rson);}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);setmid;pd(p);if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    ll query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;ll res=-INF;pd(p);if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=max(res,query(rson,pl,pr));return res;}
}T[2];
using namespace __gnu_pbds;
tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update> tre;
void matt(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    for(int i=1;i<=n;i++)   c[i]=a[i]-(b[i]<0);
    discrete();
    T[0].build(all);T[1].build(all);
    T[0].mdf(1,0);T[1].mdf(1,0);
    for(int i=1;i<=n;i++){
        ll dp;
        if(b[i]>=0)
            dp=(c[i]>1?T[1].query(all,1,c[i]-1)-1ll*a[i]*m:-INF);
            // for(int j=0;j<a[i];j++)    dp[a[i]]=max(dp[a[i]],dp[j]-1ll*(a[i]-j)*m);
        else
            dp=T[0].query(all,c[i]+1,siz);
            // for(int j=a[i];j<=maxn-10;j++)   dp[a[i]-1]=max(dp[a[i]-1],dp[j]);
        T[0].mdf(c[i],dp);T[1].mdf(c[i],dp+1ll*d[c[i]]*m);
        T[0].upd(all,A[i],siz,b[i]);T[1].upd(all,A[i],siz,b[i]);
        // for(int j=a[i];j<=maxn-10;j++)  dp[j]+=b[i];
    }
    ll ans=T[0].tr[1];
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}