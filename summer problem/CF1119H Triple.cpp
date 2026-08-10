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
const int maxn=1e5+10,maxk=20,maxK=(1<<17)+10,mod=998244353,inv2=mod+1>>1,inv4=1ll*inv2*inv2%mod;
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
int n,k,K;ll X,Y,Z;
void XORFWT(ll a[]){
    for(int i=0;i<k;i++){
        for(int j=0;j<=K;j++)if(!(j&(1<<i))){
            ll x=a[j],y=a[j^(1<<i)];
            a[j]=x+y;a[j^(1<<i)]=x-y;
        }
    }
}
void RXORFWT(int a[]){
    for(int i=0;i<k;i++){
        for(int j=0;j<=K;j++)if(!(j&(1<<i))){
            int x=a[j],y=a[j^(1<<i)];
            a[j]=immul(imadd(x,y),inv2);a[j^(1<<i)]=immul(imdel(x,y),inv2);
        }
    }
}
int a[maxn],b[maxn],c[maxn];
ll p1[maxK],p2[maxK],p3[maxK];int s[maxK];
int sa;
inline int md(ll x){x%=mod;(x<0)&&(x+=mod);return x;}
int main(){
    scanf("%d%d%d%d%d",&n,&k,&X,&Y,&Z);K=(1<<k)-1;
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a[i],&b[i],&c[i]);
        b[i]^=a[i];c[i]^=a[i];sa^=a[i];
        p1[b[i]]++;p2[c[i]]++;p3[b[i]^c[i]]++;
    }
    XORFWT(p1);XORFWT(p2);XORFWT(p3);
    // for(int i=0;i<=K;i++)printf("%d ",p1[i]);puts("");
    // for(int i=0;i<=K;i++)printf("%d ",p2[i]);puts("");
    // for(int i=0;i<=K;i++)printf("%d ",p3[i]);puts("");
    for(int i=0;i<=K;i++){
        int c1=(n+p1[i]+p2[i]+p3[i])/4,
        c2=(n+p1[i]-2*c1)/2,c3=(n+p2[i]-2*c1)/2,c4=(n+p3[i]-2*c1)/2;
        s[i]=qpow(md(X+Y+Z),c1);mmul(s[i],qpow(md(X+Y-Z),c2));
        mmul(s[i],qpow(md(X-Y+Z),c3));mmul(s[i],qpow(md(X-Y-Z),c4));
    }
    RXORFWT(s);
    for(int i=0;i<=K;i++)   printf("%d ",s[i^sa]);
}