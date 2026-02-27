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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=210,mod=1e9+7;
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
int n,lim;
int f[maxn*maxn],g[maxn*maxn],h[maxn*maxn],F[maxn][maxn*maxn],C[maxn][maxn],pq[maxn*maxn][maxn];
void init(){
    const int N=200;
    for(int i=0;i<=N;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j],C[i-1][j-1]);}
}
int main(){
    init();
    scanf("%d%d",&n,&lim);
    const int N=n*(n+1)/2;
    if(lim>N)   return puts("0"),0;
    for(int i=0;i<=N;i++)   F[0][i]=1;
    for(int x=0;x<=N;x++)for(int i=0;i<=n;i++)pq[x][i]=qpow(x,i);
    for(int i=1;i<=n;i++)
        for(int x=0;x<=N;x++)
            for(int k=0;k<i;k++)
                madd(F[i][x],1ull*C[i-1][k]*pq[x][i]%mod*F[k][x]%mod*F[i-k-1][x]%mod);
    g[0]=1;
    for(int i=0;i<=N;i++){
        for(int j=N+1;~j;j--)g[j]=imadd(immul(g[j],mod-i),j?g[j-1]:0);
    }
    for(int i=0;i<=N;i++){
        int res=1;
        for(int j=0;j<=N;j++)if(i^j)mmul(res,imdel(i,j));
        res=immul(F[n][i],qpow(res,mod-2));
        memc(h,g);
        for(int j=N+1;j>1;j--)madd(h[j-1],immul(h[j],i));
        for(int j=0;j<=N;j++)   madd(f[j],immul(res,h[j+1]));
        // for(int j=1;j<=N+1;j++)   printf("%d ",h[j]);puts("");
    }
    // for(int i=0;i<=N;i++)   printf("%d ",f[i]);puts("");
    printf("%d\n",accumulate(f+lim,f+N+1,0ll)%mod);
}