#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define ppc(x) __builtin_popcount(x)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=22,maxN=(1<<20)+10,mod=998244353;
inline int ad(int x,int y){x+=y;(x>=mod)&&(x-=mod);return x;}
inline int qp(int x,ll y){int res=1;while(y){if(y&1)res=1ull*x*res%mod;x=1ull*x*x%mod;y>>=1;}return res;}
struct mint{
    int x,k;
    mint(int a=1,int b=0){x=a;k=b;}
    inline mint operator+(mint y){if(k^y.k)return k<y.k?*this:y;return {ad(x,y.x),k};}
    inline mint operator-(mint y){y.x=mod-y.x;ad(y.x,0);return (*this)+y;}
    inline mint operator*(mint y){y.x=1ull*x*y.x%mod;y.k+=k;return y;}
    inline void operator+=(mint y){*this=*this+y;}
    inline void operator-=(mint y){*this=*this-y;}
    inline void operator*=(mint y){*this=*this*y;}
    inline void print(){printf("%d*(0^%d)\n",x,k);}
};// x*(0^k)
namespace FastMod{
    inline void madd(mint &x,mint y){x+=y;}
    inline void mdel(mint &x,mint y){x-=y;}
    inline void mmul(mint &x,mint y){x*=y;}
    inline mint imadd(mint x,mint y){return x+y;}
    inline mint imdel(mint x,mint y){return x-y;}
    inline mint immul(mint x,mint y){return x*y;}
}
using namespace FastMod;
int n,m;
int a[maxN];
mint f[maxN],g[maxN],h[maxN];
void SOS(mint*s){
    for(int i=0;i<n;i++)
        for(int j=0;j<=m;j++)
            if(!(j&(1<<i)))    mmul(s[j],s[j^(1<<i)]);
}
void ORFWT(mint *s){
    for(int i=0;i<n;i++)
        for(int j=0;j<=m;j++)
            if(j&(1<<i))    madd(s[j],s[j^(1<<i)]);
}
void IORFWT(mint *s){
    for(int i=0;i<n;i++)
        for(int j=0;j<=m;j++)
            if(j&(1<<i))    mdel(s[j],s[j^(1<<i)]);
}
void matt(){
    scanf("%d",&n);m=(1<<n)-1;
    for(int i=0;i<=m;i++)   scanf("%d",&a[i]);
    for(int i=0;i<=m;i++){
        f[i]=g[i]=mint();
        f[i].x=(a[i]+1)%mod;g[i].x=(a[i]+a[i]+1)%mod;
        if(!f[i].x) f[i]={1,1};
    }
    SOS(f);SOS(g);
    for(int i=0;i<=m;i++)   h[i].x=1ull*f[i].x*qp(mod-2,ppc(i))%mod,h[i].k=f[i].k;
    ORFWT(h);
    for(int i=0;i<=m;i++)   h[i]=immul(h[i],h[i]);
    IORFWT(h);
    // for(int i=0;i<=m;i++)   h[i].print();
    int ans=0;
    for(int i=0;i<=m;i++){
        mint p=immul(h[i],g[i]),q=immul(f[i],f[i]);
        q.x=1ull*q.x*qp(2,ppc(i))%mod;
        if(p.k^q.k) continue;
        // printf("%d : ",i);p.print();q.print();puts("");
        ans=ad(ans,1ull*p.x*qp(q.x,mod-2)%mod);
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%*d%d",&T);while(T--)matt();}