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
const int maxn=110,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn];
int dp[maxn][maxn][maxn];
int main(){
    scanf("%d",&n);
    int mx=0;
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);a[i]=min(a[i],n);mx=max(mx,a[i]);}
    for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)dp[i+1][i][j]=1;
    for(int len=1;len<=n;len++)
        for(int l=1,r=len;r<=n;l++,r++)
            for(int i=1;i<=n;i++)
                for(int x=l;x<=r;x++)   madd(dp[l][r][i],immul(dp[l][x-1][min(a[x],i)],dp[x+1][r][min(a[x],i)-1]));
    printf("%d\n",dp[1][n][mx]);
}