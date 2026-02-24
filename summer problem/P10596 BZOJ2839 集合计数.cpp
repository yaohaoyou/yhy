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
const int maxn=1e6+10,mod=1e9+7;
int n,k;
int fac[maxn],inv[maxn];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y,int p=mod){int res=1;while(y){if(y&1) res=1ll*res*x%p;x=1ll*x*x%p;y>>=1;}return res;}
}
using namespace FastMod;
void init(){
    fac[0]=1;
    for(int i=1;i<=n;i++)   fac[i]=immul(fac[i-1],i);
    inv[n]=qpow(fac[n],mod-2);
    for(int i=n-1;~i;i--)   inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
    scanf("%d%d",&n,&k);
    init();
    int ans=0;
    for(int i=k;i<=n;i++){
        int w=immul(C(n-k,i-k),qpow(2,qpow(2,n-i,mod-1))-1);
        if((i-k)&1) mdel(ans,w);
        else    madd(ans,w);
    }
    mmul(ans,C(n,k));
    printf("%d\n",ans);
}