#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define popc __builtin_popcountll
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=3e5+10,lgV=60;
int n,q;
int a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define pos p,l,r
    #define setpos int p,int l,int r
    int tr[maxn<<2][lgV];
    ll tag[maxn<<2];
    bool pc[maxn<<2];
    inline void bre(int p){for(int i=0;i<lgV;i++)tr[p][i]=popc(tr[p][i]+tag[p]);tag[p]=0;}
    inline void ptp(int p,int q){for(int i=0;i<lgV;i++)tr[p][i]=tr[q][tr[p][i]];pc[p]=true;}
    inline void pta(int p,ll s){tag[p]+=s;}
    inline void pd(int p){if(pc[p]){ptp(ls,p);ptp(rs,p);pc[p]=false;for(int i=0;i<lgV;i++)tr[p][i]=i;}if(tag[p]){pta(ls,tag[p]);pta(rs,tag[p]);tag[p]=0;}}
    void build(setpos){for(int i=0;i<lgV;i++)tr[p][i]=i;if(l==r)return pc[p]=true,tag[p]=a[l],void();setmid;build(lson);build(rson);}
    void upd(setpos){if(pc[p])return bre(p);setmid;pd(p);upd(lson);upd(rson);}
    void updadd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pta(p,s);setmid;pd(p);if(pl<=mid)updadd(lson,pl,pr,s);if(pr>mid)updadd(rson,pl,pr,s);}
    void updppc(setpos,int pl,int pr){if(l>=pl&&r<=pr)return upd(pos),pc[p]=true,void();setmid;pd(p);if(pl<=mid)updppc(lson,pl,pr);if(pr>mid)updppc(rson,pl,pr);}
    ll query(setpos,int x){
        if(l==r)    return tr[p][0]+tag[p];
        setmid;
        if(pc[p])   return x<=mid?tr[p][query(lson,x)]+tag[p]:tr[p][query(rson,x)]+tag[p];
        return x<=mid?query(lson,x)+tag[p]:query(rson,x)+tag[p];
    }
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build(all);
    while(q--){
        char c[10];int l,r,v;
        scanf("%s%d",c,&l);
        if(c[0]=='A'){scanf("%d%d",&r,&v);updadd(all,l,r,v);}
        else if(c[0]=='P'){scanf("%d",&r);updppc(all,l,r);}
        else    printf("%lld\n",query(all,l));
    }
}