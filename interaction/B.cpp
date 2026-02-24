#include<bits/stdc++.h>
#include"matrix.h"
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
const int maxn=4e6+10;
int n,k;
ll s[maxn],p[maxn],q[maxn];
ll b[maxn];
int L[maxn],R[maxn];
// inline ll ask(int x,int y){return a[x][y];}
inline int P(int x){return x-2+n+n;}
inline int Q(int x){return x+n;}
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,4*n-2
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    pii tr[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void upd(int x,int s){int p=1,l=1,r=4*n-2;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=pii(s,x);while(p>>=1)pu(p);}
    pii query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;pii res=pii(0,0);if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=max(res,query(rson,pl,pr));return res;}
}
using namespace SegmentTree;
inline ll a(int x,int y){return ask(x,y);}
inline ll x(int x,int y){return (a(x-1,y)+a(x+1,y)+a(x,y-1)+a(x,y+1)-4*a(x,y))/2;}
vector<pii> solve(int N,int id){
    n=N;
    for(int i=2;i<=n+n;i++) p[P(i)]=i;
    for(int i=1-n;i<=n-1;i++)   q[Q(i)]=i;
    if(n&1){
        {
            b[P(n)]=0;
            ll sp=0,sq=0;
            for(int i=2-n;i<=n-1;i+=2)  b[Q(i)]=x((n+i)/2,(n-i)/2),sq+=b[Q(i)];
            for(int i=3;i<=n+n;i+=2)    b[P(i)]=x((i+1)/2,(i-1)/2)-b[Q(1)],sp+=b[P(i)];
            ll pn=(sq-sp)/(n+n-2);
            for(int i=2-n;i<=n-1;i+=2)  s[Q(i)]=b[Q(i)]-pn;
            for(int i=3;i<=n+n;i+=2)    s[P(i)]=pn+b[P(i)];
        }
        {
            b[P(n+1)]=0;
            ll sp=0,sq=0;
            for(int i=1-n;i<=n-1;i+=2)  b[Q(i)]=x((n+1+i)/2,(n+1-i)/2),sq+=b[Q(i)];
            for(int i=2;i<=n+n;i+=2)    b[P(i)]=x(i/2,i/2)-b[Q(0)],sp+=b[P(i)];
            ll pn1=(sq-sp)/(n+n);
            for(int i=1-n;i<=n-1;i+=2)  s[Q(i)]=b[Q(i)]-pn1;
            for(int i=2;i<=n+n;i+=2)    s[P(i)]=pn1+b[P(i)];
        }
    }
    else{
        {
            b[P(n+1)]=0;
            ll sp=0,sq=0;
            for(int i=1-n;i<=n-1;i+=2)  b[Q(i)]=x((n+1+i)/2,(n+1-i)/2),sq+=b[Q(i)];
            for(int i=3;i<=n+n;i+=2)    b[P(i)]=x((i+1)/2,(i-1)/2)-b[Q(1)],sp+=b[P(i)];
            ll pn1=(sq-sp)/(n+n-1);
            for(int i=1-n;i<=n-1;i+=2)  s[Q(i)]=b[Q(i)]-pn1;
            for(int i=3;i<=n+n;i+=2)    s[P(i)]=pn1+b[P(i)];
        }
        {
            b[P(n)]=0;
            ll sp=0,sq=0;
            for(int i=2-n;i<=n-1;i+=2)  b[Q(i)]=x((n+i)/2,(n-i)/2),sq+=b[Q(i)];
            for(int i=2;i<=n+n;i+=2)    b[P(i)]=x(i/2,i/2)-b[Q(0)],sp+=b[P(i)];
            ll pn=(sq-sp)/(n+n-1);
            for(int i=2-n;i<=n-1;i+=2)  s[Q(i)]=b[Q(i)]-pn;
            for(int i=2;i<=n+n;i+=2)    s[P(i)]=pn+b[P(i)];
        }
    }
    vector<int> vp[2],vq[2];
    for(int i=2;i<=n+n;i++) L[P(i)]=Q(max(2-i,i-n-n)),R[P(i)]=Q(min(n+n-i,i-2)),vp[i&1].eb(P(i));
    for(int i=1-n;i<=n-1;i++)   vq[abs(i)&1].eb(Q(i));
    vector<pii> ans;
    for(int o:{0,1}){
        for(int i:vq[o])    upd(i,s[i]);
        sort(vp[o].begin(),vp[o].end(),[&](int x,int y){return R[x]-L[x]<R[y]-L[y];});
        for(int i:vp[o]){
            vector<pii> tmp;tmp.clear();
            while(s[i]--){
                pii x=query(all,L[i],R[i]);assert(x.fi);
                if(x.fi>1)  tmp.eb(x.fi-1,x.se);
                ans.eb((p[i]+q[x.se])/2,(p[i]-q[x.se])/2);
                upd(x.se,0);
            }
            for(auto [i,j]:tmp) upd(j,i);
        }
    }
    // for(auto [i,j]:ans) printf("%d %d\n",i,j);
    return ans;
    // for(auto [i,j]:s)if(j)printf("P[%d] = %d\n",i,j);
    // for(auto [i,j]:s)if(j)printf("Q[%d] = %d\n",i,j);
    // for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)printf("P(%d) Q(%d) (%d,%d)\n",i+j,i-j,i,j);
}
// a+b=i,a-b\in[max(2-i,i-2n),min(2n-i,i-2)]