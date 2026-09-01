#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e5+10;
int n;
int a[maxn],b[maxn],c[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    pli tr[maxn<<2];
    int pos[maxn];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    void build(setpos){if(l==r)return pos[l]=p,tr[p]=pli(1e18,l),void();setmid;build(lson);build(rson);pu(p);}
    pli query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;pli res=pli(1e18,1e9);if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=min(res,query(rson,pl,pr));return res;}
    inline void upd(int x,ll s){int p=pos[x];tr[p]=pli(s,x);while(p>>=1)pu(p);}
}
using namespace SegmentTree;
stack<int> stk;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    ll ans=0;
    build(all);upd(1,b[a[1]]);stk.ep(1);
    for(int i=2;i<=n;i++){
        while(!stk.empty()&&a[stk.top()]<a[i])  stk.pop();
        int l=stk.empty()?1:stk.top();
        stk.ep(i);
        pli x=query(all,l,i);
        c[a[x.se]]++;
        ans+=x.fi;upd(x.se,b[a[x.se]]*(1ll*(c[a[x.se]]+1)*(c[a[x.se]]+1)-1ll*c[a[x.se]]*c[a[x.se]]));
        upd(i,b[a[i]]);
    }
    printf("%lld\n",ans);
}