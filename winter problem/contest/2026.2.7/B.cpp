#pragma GCC optimize(2,3,"Ofast")
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
const int maxn=2e5+10,N=2e5,mod=998244353;
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
int n,q;
int a[maxn],f[maxn],lst[maxn],ans[maxn];
vector<pii> Q[maxn];
vector<int> fac[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2];
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return gmx(tr[p],s);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);}
    inline int query(int x){int p=1,l=1,r=n,res=0;while(l^r){setmid;gmx(res,tr[p]);(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}gmx(res,tr[p]);return res;}
}
using namespace SegmentTree;
void init(){
    for(int i=1;i<=N;i++)
        for(int j=i;j<=N;j+=i)fac[j].eb(i);
}
int main(){
    init();
    scanf("%*d%d%d",&n,&q);
    f[1]=f[2]=1;
    for(int i=3;i<=N;i++)   f[i]=imadd(f[i-1],f[i-2]);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=q;i++){int l,r;scanf("%d%d",&l,&r);Q[r].eb(l,i);}
    for(int i=1;i<=n;i++){
        if(i^1) upd(all,i-1,i-1,__gcd(a[i-1],a[i]));
        for(int j:fac[a[i]]){
            if(!lst[j]) continue;
            upd(all,1,lst[j],j);
        }
        for(auto [j,id]:Q[i])   ans[id]=f[query(j)];
        for(int j:fac[a[i]])    lst[j]=i;
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}