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
const ll inf=2e18;
int n,m;
int a[maxn];ll b[maxn];
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll tr[maxn<<2],tag[maxn<<2];
    inline void pt(int p,ll s){tr[p]+=s;tag[p]+=s;}
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void pd(int p){if(tag[p]){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=0;}}
    void build(setpos){if(l==r)return tr[p]=b[l],void();setmid;build(lson);build(rson);pu(p);}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    ll query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid;ll res=-inf;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=max(res,query(rson,pl,pr));return res;}
}T[2];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   b[i]=a[i]+a[i+1];b[n]=-inf;
    T[0].build(all);
    for(int i=1;i<=n;i++)   b[i]=a[i]+a[i+1]+a[i+2];b[n-1]=b[n]=-inf;
    T[1].build(all);
    auto print=[&](ll x,ll y){if(!x)puts("0/1");else{ll g=abs(__gcd(x,y));printf("%lld/%lld\n",x/g,y/g);}};
    while(m--){
        int op,l,r,x;
        scanf("%d%d%d",&op,&l,&r);
        if(op==1){
            scanf("%d",&x);
            if(r>1)T[0].upd(all,max(1,l-1),r-1,x);T[0].upd(all,l,r,x);
            if(r>2)T[1].upd(all,max(1,l-2),r-2,x);if(r>1)T[1].upd(all,max(1,l-1),r-1,x);T[1].upd(all,l,r,x);
        }
        else{
            if(r-l+1==2)    print(T[0].query(all,l,r-1),2);
            else{
                ll x=T[0].query(all,l,r-1),y=T[1].query(all,l,r-2);
                if(3ll*x>2ll*y) print(x,2);
                else    print(y,3);
            }
        }
    }
}