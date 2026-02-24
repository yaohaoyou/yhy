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
const int maxn=2e5+10;
const ll INF=1e18;
int n;
int a[maxn],b[maxn],p[maxn],v[maxn],vv[maxn];
// ll f[maxn][maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void pt(int p,ll s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){tr[p]=-INF;tag[p]=0;if(l==r)return;setmid;build(lson);build(rson);}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    inline void upd(int x,ll s){int p=1,l=0,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=max(tr[p],s);while(p>>=1)pu(p);}
    ll query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid;ll res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=max(res,query(rson,pl,pr));return res;}
}
using namespace SegmentTree;
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&v[i]),vv[i]=v[i];
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),v[i]=vv[a[i]];
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]),p[b[i]]=i;
    for(int i=1;i<=n;i++)   a[i]=p[a[i]];
    // mems(f,-0x3f);
    // f[0][0]=0;
    build(all);
    upd(0,0);
    ll ans=0;
    for(int i=1;i<=n;i++){
        // for(int j=0;j<=a[i];j++)    f[i][j]=max(f[i][j],f[i-1][j]+v[i]),f[i][a[i]]=max(f[i][a[i]],f[i-1][j]);
        // for(int j=a[i]+1;j<=n;j++)  f[i][j]=f[i-1][j];
        // for(int j=0;j<=n;j++)   ans=max(ans,f[i][j]);
        upd(a[i],query(all,0,a[i]));
        upd(all,0,a[i]-1,v[i]);
        ans=max(ans,tr[1]);
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}