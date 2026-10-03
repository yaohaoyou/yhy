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
const int maxn=2510,mod=1e9+7;
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
int n,k;
int fac[maxn*maxn],inv[maxn*maxn];
void init(){
    const int N=5e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int f[maxn][maxn]; // f[i][j] 表示从后往前填了 i 个 0，j 种数的方案数
int main(){
    init();
    scanf("%d%d",&n,&k);
    if(k==1)    return puts("1"),0;
    f[0][0]=1;
    for(int i=0;i<=n;i++){
        for(int j=i;j<=n;j++){
            madd(f[i+1][j],f[i][j]);
            madd(f[i][j+1],immul(f[i][j],C(i+j*(k-1)+k-2,k-2)));
        }
    }
    printf("%d\n",immul(f[n][n],fac[n]));
}