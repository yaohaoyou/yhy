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
const int maxn=2e5+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn],b[maxn],f[maxn];
int fac[maxn],inv[maxn];
void init(){
    const int N=2e5;
    fac[0]=1;for(int i=1;i<=N;i++)  fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--) inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
    init();
    ll sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),sum+=a[i];
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    int ans=0;
    for(int i=1;i<=n;i++)   madd(ans,1ll*qpow(2,sum-a[i])*imdel(qpow(1+b[i],a[i]),1)%mod);
    printf("%d\n",ans);
}