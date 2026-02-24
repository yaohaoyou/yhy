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
int n,q,mod;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],mul[maxn<<2],add[maxn<<2],len[maxn<<2];
    inline void pu(int p){tr[p]=imadd(tr[ls],tr[rs]);}
    inline void ptmul(int p,int s){mmul(tr[p],s);mmul(add[p],s);mmul(mul[p],s);}
    inline void ptadd(int p,int s){madd(tr[p],immul(len[p],s));madd(add[p],s);}
    inline void pd(int p){if(mul[p]^1)ptmul(ls,mul[p]),ptmul(rs,mul[p]),mul[p]=1;if(add[p])ptadd(ls,add[p]),ptadd(rs,add[p]),add[p]=0;}
    void updadd(setpos,int pl,int pr,int s){if(l^r)pd(p);if(l>=pl&&r<=pr)return ptadd(p,s);setmid;if(pl<=mid)updadd(lson,pl,pr,s);if(pr>mid)updadd(rson,pl,pr,s);pu(p);}
    void updmul(setpos,int pl,int pr,int s){if(l^r)pd(p);if(l>=pl&&r<=pr)return ptmul(p,s);setmid;if(pl<=mid)updmul(lson,pl,pr,s);if(pr>mid)updmul(rson,pl,pr,s);pu(p);}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)madd(res,query(rson,pl,pr));return res;}
    void build(setpos){mul[p]=1;add[p]=0;if(l==r)return tr[p]=a[l],len[p]=1,void();setmid;build(lson);build(rson);pu(p);len[p]=len[ls]+len[rs];}
}
using namespace SegmentTree;
int main(){
    scanf("%d%d%d",&n,&q,&mod);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    build(all);
    while(q--){
        int op,l,r,k;scanf("%d%d%d",&op,&l,&r);
        if(op==1){scanf("%d",&k);updmul(all,l,r,k);}
        else if(op==2){scanf("%d",&k);updadd(all,l,r,k);}
        else    printf("%d\n",query(all,l,r));
    }
}