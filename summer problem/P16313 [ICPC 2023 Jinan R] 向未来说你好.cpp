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
const int maxn=2e5+10,mod=998244353;
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
int a[maxn],b[maxn],f[maxn],g[maxn],h[maxn];
pii mx[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){if(x<=0)return;while(x<=n){madd(tr[x],s);x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){madd(res,tr[x]);x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:imdel(que(r),que(l-1));}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
void divide(int l,int r){
    if(l==r){
        if(a[l]==1) madd(f[l],f[l-1]);
        return;
    }
    int mid=(l+r)>>1;
    divide(l,mid);
    b[mid]=a[mid];b[mid+1]=a[mid+1];
    for(int i=mid-1;i>=l;i--)   b[i]=max(b[i+1],a[i]);
    for(int i=mid+2;i<=r;i++)   b[i]=max(b[i-1],a[i]);
    auto mdf=[&](int x,int o){if(o==1)T.add(x+b[x]-1,f[x-1]);else if(f[x-1])T.add(x+b[x]-1,mod-f[x-1]);};
    for(int i=l;i<=mid;i++)mdf(i,1);
    int i=mid;
    for(int j=mid+1;j<=r;j++){
        while(i>=l&&i>j-b[j]+1) mdf(i--,-1);
        if(i+1<=mid&&i+1<=j-b[j]+1)  mdf(++i,1);
        madd(f[j],T.que(j));
        // if(j==n)    printf("[%d,%d] %d : %d\n",l,r,i,T.que(j));
    }
    while(i>=l)mdf(i--,-1);
    divide(mid+1,r);
}
void dvd2(int l,int r){
    if(l==r){
        if(a[l]^1)  madd(h[l],immul(f[l-1],g[l+1]));
        return;
    }
    int mid=(l+r)>>1;dvd2(l,mid);dvd2(mid+1,r);
    mx[mid]=pii(a[mid],mid);b[mid]=0;
    mx[mid+1]=pii(a[mid+1],mid+1);b[mid+1]=0;
    for(int i=mid-1;i>=l;i--){
        mx[i]=mx[i+1];b[i]=b[i+1];
        if(a[i]>mx[i].fi)b[i]=mx[i].fi,mx[i]=pii(a[i],i);
        else gmx(b[i],a[i]);
    }
    for(int i=mid+2;i<=r;i++){
        mx[i]=mx[i-1];b[i]=b[i-1];
        if(a[i]>mx[i].fi)b[i]=mx[i].fi,mx[i]=pii(a[i],i);
        else gmx(b[i],a[i]);
    }
    // printf("[%d,%d]\n",l,r);
    {
        auto mdf=[&](int x,int o){if(o==1)T.add(x-mx[x].fi+1,g[x+1]);else if(g[x+1])T.add(x-mx[x].fi+1,mod-g[x+1]);};
        int jl=mid+1,j=mid;
        for(int i=mid;i>=l;i--){
            int L=b[i]+i-1,R=mx[i].fi+i-2;
            if(j>mid&&j>R)   mdf(j--,-1);
            while(j+1<=r&&j+1<=R)   mdf(++j,1);
            while(jl<=r&&jl<L)  mdf(jl++,-1);
            if(jl-1>=mid+1&&jl-1>=L) mdf(--jl,1);
            // if(mx[i].se==5) printf("[%d,%d] %d\n%d : %d\n",l,r,i,mx[i].se,T.query(i,n));
            madd(h[mx[i].se],immul(f[i-1],T.query(i,n)));
        }
        while(jl<=j)    mdf(jl++,-1);
    }
    {
        auto mdf=[&](int x,int o){if(o==1)T.add(x+mx[x].fi-1,f[x-1]);else if(f[x-1])T.add(x+mx[x].fi-1,mod-f[x-1]);};
        int ir=mid,i=mid+1;
        for(int j=mid+1;j<=r;j++){
            int L=j-mx[j].fi+2,R=j-b[j]+1;
            if(i<=mid&&i<L)  mdf(i++,-1);
            while(i-1>=l&&i-1>=L)   mdf(--i,1);
            while(ir>=l&&ir>R)    mdf(ir--,-1);
            if(ir+1<=mid&&ir+1<=R)   mdf(++ir,1);
            madd(h[mx[j].se],immul(g[j+1],T.que(j)));
            // printf("# %d : %d\n",mx[j].se,T.que(j));
        }
        while(ir>=i)    mdf(ir--,-1);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    reverse(a+1,a+n+1);
    f[0]=1;divide(1,n);
    memc(g,f);reverse(g,g+n+2);
    mems(f,0);
    reverse(a+1,a+n+1);
    f[0]=1;divide(1,n);
    // for(int i=1;i<=n;i++)   printf("%d ",f[i]);puts("");
    // for(int i=1;i<=n;i++)   printf("%d ",g[i]);puts("");
    dvd2(1,n);
    for(int i=1;i<=n;i++)   printf("%d ",imadd(h[i],f[n]));
}