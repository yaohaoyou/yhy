#include<bits/stdc++.h>
#define _pop(x) __builtin_popcount(x)
using namespace std;
const int maxn=1e6+10;
int n,l,r,cnt;
inline void out(int pl,int pr){
    // printf("**%d %d\n",pl,pr);
    pl--;pr--;
    int i=__lg(pr-pl+1),j=pl/(1<<i);
    // cout<<"? "<<i<<' '<<j<<endl;
    cnt++;
}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    int query(int p,int l,int r,int pl,int pr){
        // printf("%d %d %d %d %d\n",p,l,r,pl,pr);
        if(l>=pl&&r<=pr){
            int x=0;
            out(l,r);
            cin>>x;
            return x;
        }
        int mid=(l+r)>>1,res=0;
        if(pr<=mid) return query(lson,pl,pr);
        if(pl>mid)  return query(rson,pl,pr);
        int c1=_pop(pr-mid)+_pop(mid-pl+1),c2=1;
        if(pl-1>=l) c2+=_pop(pl-l);
        if(pr+1<=r) c2+=_pop(r-pr);
        if(c1<=c2)  res=(query(lson,pl,mid)+query(rson,mid+1,pr))%100;
        else{
            int x;
            out(l,r);
            cin>>x;
            res=x;
            if(pl-1>=l)    res=(res-query(lson,l,pl-1)+100)%100;
            if(pr+1<=r)    res=(res-query(rson,pr+1,r)+100)%100;
        }
        return res;
    }
}
using namespace SegmentTree;
int main(){    freopen("data.in","r",stdin);freopen("mine.out","w",stdout);

    cin>>n>>l>>r;
    l++;r++;
    n=1<<n;
    int res=query(1,1,n,l,r);
    // cout<<"! "<<res<<endl;
    printf("%d\n",cnt);
}