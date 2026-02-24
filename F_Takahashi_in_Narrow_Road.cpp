#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int maxn=3e5+10;
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
    ll tr[maxn<<2],tag[maxn<<2],L[maxn<<2];
    inline void pushtag(setpos,int s){tr[p]=1ll*(r-l+1)*s;L[p]=s+l;tag[p]=s;}
    inline void pushdown(setpos){if(!tag[p])return;setmid;pushtag(lson,tag[p]);pushtag(rson,tag[p]);tag[p]=0;}
    inline void pushup(int p){tr[p]=tr[ls]+tr[rs];L[p]=L[ls];}
    void update(setpos,int pl,int pr,int s){
        if(l>=pl&&r<=pr)    return pushtag(p,l,r,s);
        setmid;
        pushdown(p,l,r);
        if(pl<=mid) update(lson,pl,pr,s);
        if(pr>mid)  update(rson,pl,pr,s);
        pushup(p);
    }
    ll query(setpos,int pl,int pr){
        if(l>=pl&&r<=pr)    return tr[p];
        setmid;ll res=0;
        pushdown(p,l,r);
        if(pl<=mid) res=query(lson,pl,pr);
        if(pr>mid)  res+=query(rson,pl,pr);
        return res;
    }
    int binary(setpos,int s){
        if(l==r)    return l;
        setmid; 
        pushdown(p,l,r);
        if(L[rs]<=s)    return binary(rson,s);
        return binary(lson,s);
    }
}
using namespace SegmentTree;
inline int en(int x){
    // int l=1,r=n,ret=0;
    // while(l<=r){
    //     setmid;
    //     if(query(all,mid,mid)+mid<=x){ret=mid;l=mid+1;}
    //     else r=mid-1;
    // }
    // printf("%d : %d %d\n",x,ret,query(all,1,1)+1<=x?binary(all,x):0);
    return query(all,1,1)+1<=x?binary(all,x):0;
}
ll ans;
inline ll calc(int l,int r,int L,int R){return abs(query(all,l,r)+1ll*(l+r)*(r-l+1)/2-1ll*(L+R)*(R-L+1)/2);}
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   update(all,i,i,a[i]-i);
    scanf("%d",&q);
    while(q--){
        int x,xs,y,ys;
        scanf("%d%d",&x,&ys);
        xs=query(all,x,x)+x;
        if(xs<=ys){
            int l=ys,r=2e8,res;
            while(l<=r){
                setmid;
                int em=en(mid);
                if(em-x+1<=mid-ys+1)    res=mid,r=mid-1;
                else    l=mid+1;
            }
            int er=en(res);
            // [x,er] -> [ys,ys-x+er]
            ans+=calc(x,er,ys,ys-x+er);
            // printf("res = %d\n",res);
            update(all,x,er,ys-x);
        }
        else{
            int l=-1e8,r=ys,res;
            while(l<=r){
                setmid;
                int em=en(mid)+1;
                if(x-em+1<=ys-mid+1)    res=mid,l=mid+1;
                else    r=mid-1;
            }
            int er=en(res)+1;
            // printf("[%d,%d] -> [%d,%d]\n",er,x,ys-x+er,ys);
            ans+=calc(er,x,ys-x+er,ys);
            update(all,er,x,ys-x);
        }
    }
    printf("%lld\n",ans);
}