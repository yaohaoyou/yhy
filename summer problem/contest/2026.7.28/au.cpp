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
const int maxn=5010;
int n,mod;
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
int f[maxn],fac[maxn];
int C[maxn][maxn];
int main(){
    freopen("au.in","r",stdin);freopen("au.out","w",stdout);
    scanf("%d%d",&n,&mod);if(n==2)return puts("0"),0;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=immul(fac[i-1],i);
    for(int i=0;i<=n;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}
    int sz=n-1-(n+1)/2;
    sz=min(sz,(n+3)/4-1);
    int ans=0;
    for(int i=n/2;i<n;i++){
        int res=qpow(i,n-i-1);
        for(int j=sz+1;j<=n-i-1;j++) mdel(res,immul(i,immul(C[n-i-1][j],qpow(i-1,n-i-1-j))));
        // printf("res = %d\n",immul(n,immul(C[n-1][i],res)),1ull*C[n-1][i]*n%mod*(n-2)%mod);
        madd(ans,immul(C[n-1][i],res));
    }
    // for(int i=n/2;i<n;i++){
        // madd(ans,immul(g[i][n-1],qpow(fac[i],mod-2)));
        // printf("res = %d\n",immul(g[i][n-1],qpow(fac[i],mod-2)));
    // }
    mmul(ans,n);
    printf("%d\n",ans);
}