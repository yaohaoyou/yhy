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
const int maxn=5e6+10,mod=998244353;
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
int n,k;
int g[maxn],fac[maxn],inv[maxn];
void init(){
    const int N=5e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    g[0]=1;
    for(int i=2;i<=N;i++)   g[i]=1ull*2*i%mod*(2*i-2)%mod*(1ull*2*(i-1)*g[i-2]%mod+g[i-1])%mod;
}
inline int A(int x,int y){return 1ull*fac[x]*inv[x-y]%mod;}
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void matt(){
    scanf("%d%d",&n,&k);
    printf("%d\n",1ull*C(n,k)*A(n,k)%mod*qpow(2,k)%mod*g[n-k]%mod);
}
int main(){init();int T;scanf("%d",&T);while(T--)matt();}
/*
g(x) 表示 x 对错排的方案数
g(x)=(2x)*(2x-2)*((x-1)*2*g(x-2)+g(x-1))
*/