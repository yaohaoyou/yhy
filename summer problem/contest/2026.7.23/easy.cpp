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
const int maxn=2e5+10,mod=998244353,inv2=(mod+1)>>1;
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
int fac[maxn],inv[maxn];
void init(){
    const int N=maxn-10;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int n,m,ans;
int a[maxn];
int main(){
    freopen("easy.in","r",stdin);freopen("easy.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int x=immul(n+1,inv2);
    for(int i=1;i<=n;i++)   madd(ans,immul(i,i));
    for(int i=1;i<=n;i++){
        int p=(1ll*i*(i-1)/2+1ll*(n-i)*(n-i+1)/2)%mod;
        mmul(p,qpow(1ll*n*(n+1)/2%mod,mod-2));
        p=qpow(p,m);
        madd(ans,immul(p,immul(mod-a[i],i)));
        madd(ans,immul(1+mod-p,immul(mod-a[i],x)));
    }
    mmul(ans,qpow(1ll*n*(n+1)/2%mod,m));
    printf("%d\n",ans);
}