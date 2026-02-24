#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int maxn=1e6+10,base=547,base2=2,inf=2e9;
int n,q;
int a[maxn];
inline ull qpow(ull x,int y){
    ull res=1;
    while(y){
        if(y&1) res=res*x;
        x=x*x;
        y>>=1;
    }
    return res;
}
ull hsh[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    ull tr[maxn<<2],tr2[maxn<<2];
    int mn[maxn<<2];
    inline void pushup(int p){tr[p]=tr[ls]+tr[rs];tr2[p]=tr2[ls]+tr2[rs];mn[p]=min(mn[ls],mn[rs]);}
    void build(int p,int l,int r){
        if(l==r)    return tr[p]=qpow(base,a[l]),tr2[p]=qpow(base2,a[l]),mn[p]=a[l],void();
        setmid;
        build(lson);build(rson);
        pushup(p);
    }
    void update(int p,int l,int r,int x){
        if(l==r)    return tr[p]=qpow(base,a[l]),tr2[p]=qpow(base2,a[l]),mn[p]=a[l],void();
        setmid;
        if(x<=mid)  update(lson,x);
        else    update(rson,x);
        pushup(p);
    }
    ull query(int p,int l,int r,int pl,int pr){
        if(l>=pl&&r<=pr)    return tr[p];
        setmid;
        ull res=0;
        if(pl<=mid) res=query(lson,pl,pr);
        if(pr>mid)  res+=query(rson,pl,pr);
        return res;
    }
    ull query2(int p,int l,int r,int pl,int pr){
        if(l>=pl&&r<=pr)    return tr2[p];
        setmid;
        ull res=0;
        if(pl<=mid) res=query2(lson,pl,pr);
        if(pr>mid)  res+=query2(rson,pl,pr);
        return res;
    }
    int querymin(int p,int l,int r,int pl,int pr){
        if(l>=pl&&r<=pr)    return mn[p];
        setmid,res=inf;
        if(pl<=mid) res=querymin(lson,pl,pr);
        if(pr>mid)  res=min(res,querymin(rson,pl,pr));
        return res;
    }
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build(1,1,n);
    while(q--){
        int opt,l,r;
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==1){
            a[l]=r;
            update(all,l);
        }
        else{
            int pl=querymin(all,l,r),pr=pl+r-l;
            if((query(all,l,r)*(base-1)==(qpow(base,pr+1)-qpow(base,pl)))&&(query2(all,l,r)*(base2-1)==(qpow(base2,pr+1)-qpow(base2,pl))))  puts("damushen");
            else    puts("yuanxing");
        }
    }
}