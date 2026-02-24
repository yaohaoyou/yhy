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
const int maxn=2010,mod=998244353;
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
int n,m,k;
int ans[maxn<<1],fac[maxn],inv[maxn];
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void init(){
    const int N=2000;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
int main(){
    init();
    scanf("%d%d%d",&n,&m,&k);
    if(k==1){
        printf("1 ");
        for(int i=min(n,m)+1;i<n+m;i++) printf("0 ");
        puts("");
        return 0;
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
        if(i==n&&j==m)  continue;
        int w=immul(C(m,j),C(n,i));
        if(i^n) mmul(w,immul(C(n-i-1,k-2),fac[k-1]));
        if(j^m) mmul(w,immul(C(m-j-1,k-2),fac[k-1]));
        madd(ans[n+m-max(i,j)],w);
    }
    for(int i=min(n,m);i<n+m;i++)   printf("%d ",ans[i]);
}