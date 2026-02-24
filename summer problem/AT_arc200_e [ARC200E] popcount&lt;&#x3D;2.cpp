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
const int mod=998244353;
int n,m;
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
inline int C2(int x){return 1ll*x*(x-1)/2%mod;}
inline int C3(int x){return __int128(x)*(x-1)*(x-2)/6%mod;}
void matt(){
    scanf("%d%d",&n,&m);
    int ans=qpow(m+1,n-1);
    madd(ans,immul(C2(m),imdel(qpow(4,n-1),qpow(3,n-1))));
    if(n>2&&m>2) madd(ans,1ll*m*(1ll*qpow(m+1,n-1)-qpow(2,n-1)-immul(m-1,imdel(qpow(3,n-1),qpow(2,n-1)))+mod+mod)%mod);
    if(n>3&&m>=3) madd(ans,1ll*C3(m)*(1ll*qpow(4,n-1)-qpow(3,n)+3ll*qpow(2,n-1)-1+mod)%mod);
    mmul(ans,qpow(2,m));
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}