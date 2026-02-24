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
const int maxn=5e5+10,mod=998244353;
int n,k;
int fac[maxn],inv[maxn];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
inline int C(int x,int y){return x<y?0:1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
    scanf("%d%d",&n,&k);
    fac[0]=1;for(int i=1;i<=n;i++)   fac[i]=immul(fac[i-1],i);
    inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;i--) inv[i]=immul(inv[i+1],i+1);
    int ans=fac[n];
    if(n==k)    return printf("%d\n",ans),0;
    for(int i=1;i<=n;i++){
        madd(ans,1ll*C(n-i,k-1)*fac[k-1]%mod*fac[n-k]%mod*(n-k)%mod);
        madd(ans,1ll*C(n-i,k)*fac[k]%mod*fac[n-k-1]%mod*(n-k)%mod);
        mdel(ans,1ll*C(n-i,k-1)*fac[n-k-1]%mod*fac[k-1]%mod*(n-k)%mod*(i-1)%mod);
    }
    printf("%d\n",ans);
}