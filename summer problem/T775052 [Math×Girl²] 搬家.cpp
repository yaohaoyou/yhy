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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e7+10,mod=998244353;
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
int fac[maxn],inv[maxn];
void init(){
    const int N=1e7;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y||x<0||y<0?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
    init();
    scanf("%d%d",&n,&m);
    // if(m>=n+n)  return printf("%d\n",qpow(2,n)),0;
    int ans=0;
    if(n>=m)    ans=qpow(2,n-m);
    else{
        for(int i=1;i<=m;i++)   madd(ans,C(n,i-n));
    }
    for(int i=1;i<m;i++)   madd(ans,imadd(C(i,m-i),immul(C(i,m-i-1),qpow(2,n-i))));
    printf("%d\n",ans);
}