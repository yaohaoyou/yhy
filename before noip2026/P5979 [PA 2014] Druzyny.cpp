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
const int maxn=1e6+10,mod=1e9+7;
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
int n;
pii a[maxn];
int f[maxn],g[maxn];
pii seg[maxn];
vector<int> v[2][maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int mx[maxn<<2],tr[maxn<<2];
    inline void pu(int p){mx[p]=max(mx[ls],mx[rs]);tr[p]=mx[p]==mx[ls]?tr[ls]:0;if(mx[p]==mx[rs])madd(tr[p],tr[rs]);}
    inline void upd(int x,int w,int s){int p=1,l=1,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}mx[p]=w;tr[p]=s;while(p>>=1)pu(p);}
    pii query(setpos,int pl,int pr){
        if(l>=pl&&r<=pr)return pii(mx[p],tr[p]);
        setmid;
        if(pl>mid)  return query(rson,pl,pr);
        if(pr<=mid) return query(lson,pl,pr);
        pii L=query(lson,pl,pr),R=query(rson,pl,pr);
        if(L.fi==R.fi)  madd(L.se,R.se);
        else if(L.fi<R.fi)  L=R;
        return L;
    }
}
using namespace SegmentTree;
pii mrg(pii x,pii y){return pii(max(x.fi,y.fi),min(x.se,y.se));}
void divide(int l,int r){
    if(l==r){
        if(a[l].fi==1&&g[l-1]){
            if(f[l-1]+1>f[l])   f[l]=f[l-1]+1,g[l]=g[l-1];
            else if(f[l-1]+1==f[l]) madd(g[l],g[l-1]);
        }
        return;
    }
    int mid=(l+r)>>1;divide(l,mid);
    seg[mid]=a[mid];seg[mid+1]=a[mid+1];
    for(int i=mid-1;i>=l;i--)   seg[i]=mrg(seg[i+1],a[i]);
    for(int i=mid+2;i<=r;i++)   seg[i]=mrg(seg[i-1],a[i]);
    for(int i=l;i<=mid;i++)if(seg[i].fi<=seg[i].se){
        int L=max(i+seg[i].fi-1,mid+1),R=min(i+seg[i].se-1,r);
        if(L<=R)    v[0][L].eb(i),v[1][R+1].eb(i);
    }
    for(int i=mid+1;i<=r;i++){
        for(int j:v[0][i])  upd(j,f[j-1],g[j-1]);
        for(int j:v[1][i])  upd(j,0,0);
        v[0][i].clear();v[1][i].clear();
        int L=max(l,i-seg[i].se+1),R=min(mid,i-seg[i].fi+1);
        if(L<=R){
            pii t=query(all,L,R);t.fi++;
            if(t.se){
                if(t.fi>f[i])   f[i]=t.fi,g[i]=t.se;
                else if(t.fi==f[i]) madd(g[i],t.se);
            }
        }
    }
    for(int i:v[1][r+1])    upd(i,0,0);
    v[1][r+1].clear();
    divide(mid+1,r);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    g[0]=1;
    divide(1,n);
    if(!f[n])   puts("NIE");
    else    printf("%d %d\n",f[n],g[n]);
}