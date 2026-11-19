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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e5+10;
bool mem1;
int n;
int a[maxn],b[maxn];
int f[maxn],g[maxn];  // 第一次 & 第二次出现位置
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int mx[maxn<<2],nd[maxn<<2];
    inline void pu(int p){
        mx[p]=max(mx[ls],mx[rs]);
        if(mx[ls]>=nd[rs])  nd[p]=nd[ls];
        else    nd[p]=max(nd[ls],nd[rs]);
    }
    inline void upd(int x){
        int p=1,l=0,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}
        mx[p]=f[x];nd[p]=f[x]==g[x]?0:g[x]+1;
        // printf("%d : %d %d\n",x,mx[p],nd[p]);
        while(p>>=1)    pu(p);
    }
    int bry(){
        int p=1,l=0,r=n,m=0;
        while(l^r){
            setmid;
            // printf("[%d,%d] %d %d %d\n",l,r,m,nd[ls],nd[rs]);
            if(m>=nd[ls])   gmx(m,mx[ls]),p=rs,l=mid+1;
            else    p=ls,r=mid;
        }
        return l;
    }
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return mx[p];setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)gmx(res,query(rson,pl,pr));return res;}
}
using namespace SegmentTree;
bool mem2;
void matt(int _cases){
    fll(mx,0,(n<<2)+5);fll(nd,0,(n<<2)+5);
    scanf("%d",&n);
    fll(f,n+1,n);fll(g,n+2,n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    // if(_cases==52){
    //     for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");
    //     for(int i=1;i<=n;i++)printf("%d ",b[i]);puts("");
    // }
    for(int i=0;i<=n;i++)   upd(i);
    ll ans=0;
    for(int i=n;i;i--){
        g[a[i]]=f[a[i]];f[a[i]]=i;
        g[b[i]]=f[b[i]];f[b[i]]=i;
        upd(a[i]);upd(b[i]);
        int r=query(all,0,bry())-1;
        if(i<=r)    ans+=r-i+1;
    }
    printf("%lld\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}