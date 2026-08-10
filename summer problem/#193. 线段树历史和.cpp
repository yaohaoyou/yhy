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
int n,m;
int a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define pos p,l,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int sum[maxn<<2],tag[maxn<<2],hcnt[maxn<<2];ll his[maxn<<2],tagh[maxn<<2];
    inline void pu(int p){sum[p]=sum[ls]+sum[rs];his[p]=his[ls]+his[rs];}
    inline void ptadd(setpos,int s){tag[p]+=s;sum[p]+=s*(r-l+1);}
    inline void pthis(setpos,int s,ll v){  // s 为 his+=sum 的次数，v 为加法 tag 的历史和
        hcnt[p]+=s;his[p]+=1ll*s*sum[p]+1ll*v*(r-l+1);tagh[p]+=1ll*s*tag[p]+v;
    }
    inline void pd(setpos){
        if(hcnt[p]||tagh[p]){setmid;pthis(lson,hcnt[p],tagh[p]);pthis(rson,hcnt[p],tagh[p]);hcnt[p]=tagh[p]=0;}
        if(tag[p]){setmid;ptadd(lson,tag[p]);ptadd(rson,tag[p]);tag[p]=0;}
    }
    inline void updadd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return ptadd(pos,s);pd(pos);setmid;if(pl<=mid)updadd(lson,pl,pr,s);if(pr>mid)updadd(rson,pl,pr,s);pu(p);}
    inline ll query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return his[p];pd(pos);setmid;ll res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res+=query(rson,pl,pr);return res;}
    void build(setpos){if(l==r)return sum[p]=a[l],void();setmid;build(lson);build(rson);pu(p);}
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build(all);pthis(all,1,0);
    while(m--){
        int op,l,r,x;
        scanf("%d%d%d",&op,&l,&r);
        if(op==1)   scanf("%d",&x),updadd(all,l,r,x);
        else    printf("%lld\n",query(all,l,r));
        pthis(all,1,0);
    }
}