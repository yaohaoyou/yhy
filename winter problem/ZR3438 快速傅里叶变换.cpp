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
const int maxn=3010,maxm=3e5+10,mod=998244353;
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
int n,m;
int fac[maxm+maxn],inv[maxm+maxn];
void init(){
    const int N=3e5+3000;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int f[maxn];
int ans[maxn];
int main(){
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n&&i*j<=m;j++)   madd(f[j],immul(C(n,j),C(m-j*(i-1),n)));
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if((j-i)&1) mdel(ans[i],immul(C(j,i),f[j]));
            else madd(ans[i],immul(C(j,i),f[j]));
        }
    }
    for(int i=n;i;i--)   madd(ans[i],ans[i+1]);
    reverse(ans+1,ans+n+1);
    int all=qpow(C(m,n),mod-2);
    for(int i=1;i<=n;i++)   madd(ans[i],ans[i-1]);
    for(int i=1;i<=n;i++)   printf("%d\n",immul(ans[i],all));
}