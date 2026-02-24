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
const int maxn=1e5+10;
int n,q;
int a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],len[maxn<<2];ll his[maxn<<2];
    ll add[maxn<<2],hadd[maxn<<2];int hcnt[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];his[p]=his[ls]+his[rs];}
    inline void ptadd(int p,ll s){add[p]+=s;tr[p]+=len[p]*s;}
    inline void pthis(int p,ll s,ll hs){hcnt[p]+=s;hadd[p]+=hs+s*add[p];his[p]+=tr[p]*s+hs*len[p];}
    inline void pd(int p){if(hadd[p]||hcnt[p])pthis(ls,hcnt[p],hadd[p]),pthis(rs,hcnt[p],hadd[p]),hadd[p]=hcnt[p]=0;if(add[p])ptadd(ls,add[p]),ptadd(rs,add[p]),add[p]=0;}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return ptadd(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    ll query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return his[p];pd(p);setmid;ll res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res+=query(rson,pl,pr);return res;}
    void build(setpos){if(l==r)return len[p]=1,tr[p]=a[l],void();setmid;build(lson);build(rson);len[p]=len[ls]+len[rs];pu(p);}
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build(all);
    pthis(1,1,0);
    while(q--){
        int op,l,r,x;scanf("%d%d%d",&op,&l,&r);
        if(op==1){
            scanf("%d",&x);
            upd(all,l,r,x);
        }
        else    printf("%lld\n",query(all,l,r));
        pthis(1,1,0);
    }
}