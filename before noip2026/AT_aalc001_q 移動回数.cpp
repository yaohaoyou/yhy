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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n,m,q;
int a[maxn],b[maxn];
struct tree{
    int l,r,x;ll k;  // 出发点在 [l,r]，有 x 的位移，获得 k 的贡献
    tree operator+(tree y){
        tree res;
        int pl=y.l-x,pr=y.r-x;
        if(max(l,pl)<=min(r,pr))    return {max(l,pl),min(r,pr),x+y.x,k+y.k};
        if(l>pr)    return {l,l,x+y.x-(l-pr),k+y.k-(l-pr)};
        return {r,r,x+y.x+(pl-r),k+y.k-(pl-r)};
    }
};
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    tree tr[maxn<<2];
    int pos[maxn];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    void build(setpos){if(l==r)return pos[l]=p,void();setmid;build(lson);build(rson);}
    inline void upd(int x){
        int p=pos[x];
        if(a[x]){
            if(b[x]>=m) tr[p]={0,0,m,m};
            else tr[p]={0,m-b[x],b[x],b[x]};
        }
        else{
            if(b[x]>=m) tr[p]={m,m,-m,m};
            else    tr[p]={b[x],m,-b[x],b[x]};
        }
        while(p>>=1)pu(p);
    }
    tree Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;return pr<=mid?Q(lson,pl,pr):pl>mid?Q(rson,pl,pr):Q(lson,pl,pr)+Q(rson,pl,pr);}
}
using namespace SegmentTree;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    build(all);for(int i=1;i<=n;i++)upd(i);
    while(q--){
        int op,x,l,r;scanf("%d%d",&op,&x);
        if(op==1){a[x]^=1;upd(x);}
        else{
            scanf("%d%d",&l,&r);
            tree t=Q(all,l,r);
            if(x<=t.l)  printf("%lld\n",t.k-(t.l-x));
            else if(x<=t.r) printf("%lld\n",t.k);
            else    printf("%lld\n",t.k-(x-t.r));
        }
    }
}