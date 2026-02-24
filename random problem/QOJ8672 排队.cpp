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
const int maxn=1e6+10;
int n,q;
pii a[maxn];
int ans[maxn];
vector<pii> Q[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void pt(int p,int s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p]){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=0;}}
    inline int binary(int s){int p=1,l=1,r=n;while(l<r){setmid;pd(p);(tr[rs]>=s)?(p=rs,l=mid+1):(p=ls,r=mid);}return tr[p]>=s?l:0;}
    inline int query(int x){int p=1,l=1,r=n;while(l<r){setmid;pd(p);(x<=mid)?(r=mid,p=ls):(l=mid+1,p=rs);}return tr[p];}
    void update(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);setmid;pd(p);if(pl<=mid)update(lson,pl,pr,s);if(pr>mid)update(rson,pl,pr,s);pu(p);}
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i].fi,&a[i].se);
    for(int i=1;i<=q;i++){int l,r;scanf("%d%d",&l,&r);Q[r].eb(l,i);}
    for(int i=1;i<=n;i++){
        int l=min(i,binary(a[i].se+1)+1),r=min(i,binary(a[i].fi));
        // printf("%d %d\n",l,r);
        if(l<=r)    update(all,l,r,1);
        for(auto [j,id]:Q[i])   ans[id]=query(j);
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}
/*
0 0 0
1 0 0
2 0 0
3 1 1
*/