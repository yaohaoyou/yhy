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
const int maxn=5010,mod=998244353;
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
int a[maxn],b[maxn];
int dp[maxn][maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),b[i]=a[i]^a[i-1];
    n++;b[n]=a[n-1];
    dp[0][accumulate(b+1,b+n+1,0)]=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<=n;j++){
            if(j&&(j^n))    madd(dp[i+1][j],immul(dp[i][j],immul(j,n-j)));
            if(j>=2)    madd(dp[i+1][j-2],immul(dp[i][j],1ll*j*(j-1)/2)%mod);
            if(n-j>=2)  madd(dp[i+1][j+2],immul(dp[i][j],1ll*(n-j)*(n-j-1)/2%mod));
        }
    }
    printf("%d\n",dp[m][0]);
}