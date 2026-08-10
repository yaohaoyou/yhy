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
const int maxn=1e5+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;ll m;
int fac[maxn],inv[maxn],I[maxn];
void init(){
    const int N=1e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    int inv2=qpow(2,mod-2);
    I[0]=1;for(int i=1;i<=N;i++)I[i]=immul(I[i-1],inv2);
    // for(int i=0;i<=N;i++)   I[i]=qpow(qpow(2,i),mod-2);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void matt(){
    scanf("%d%lld",&n,&m);
    if(m>n) return puts("0"),void();
    if(m==n)    return printf("%d\n",immul(fac[n-1],I[1])),void();
    if(!m)  return puts("1"),void();
    int ans=0;
    for(int i=0;i<=n-m;i++){  // i 个孤立点,n-m-i 条路径
        int res=1ull*C(n-m,i)*C(m-1,n-m-i-1)%mod;
        mmul(res,1ull*fac[n]*inv[n-m]%mod*I[n-m-i]%mod);
        madd(ans,res);
    }
    printf("%d\n",ans);
}
int main(){init();int T;scanf("%d",&T);while(T--)matt();}