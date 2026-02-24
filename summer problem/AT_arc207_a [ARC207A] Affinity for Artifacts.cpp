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
const int maxn=110,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;ll x;
int a[maxn],cnt[maxn],dp[maxn][maxn][maxn*maxn],f[maxn][maxn*maxn];  // dp[i][j][k] 表示已经填了 [0,i] 的数，已有 j 对 (a,b) 已匹配，和为 k 的方案数
int main(){
    scanf("%d%lld",&n,&x);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)if(a[i]>=n)x-=(a[i]-n+1),a[i]=n-1;
    x=-x;
    for(int i=1;i<=n;i++)x+=a[i],cnt[a[i]]++;
    dp[0][0][0]=1;
    const int m=n*n;
    if(x>m) return puts("0"),0;
    for(int i=0,s=0;i<n;i++){
        for(int _=1;_<=cnt[i];_++){
            if(_==1&&i)    memc(f,dp[i-1]);
            else memc(f,dp[i]);
            mems(dp[i],0);
            for(int j=0;j<=n;j++){
                for(int k=0;k<=m;k++){
                    if(i>j) madd(dp[i][j+1][k],immul(f[j][k],i-j));
                    if(n-s-i+j>0&&k+i<=m)   madd(dp[i][j][k+i],immul(f[j][k],n-s-i+j));
                }
            }
            s++;
        }
        if(!cnt[i]&&i) memc(dp[i],dp[i-1]);
        memc(f,dp[i]);mems(dp[i],0);
        for(int j=0;j<=n;j++){
            for(int k=0;k<=m;k++){
                if(s>j) madd(dp[i][j+1][k],immul(f[j][k],s-j));
                if(n-s-i+j>0&&k+i<=m)   madd(dp[i][j][k+i],immul(f[j][k],n-s-i+j));
            }
        }
        // for(int j=0;j<=n;j++)for(int k=0;k<=m;k++)if(dp[i][j][k])printf("%d %d %d : %d\n",i,j,k,dp[i][j][k]);
    }
    // printf("x = %d\n",x);
    int ans=0;
    for(int i=max(0ll,x);i<=m;i++)   madd(ans,dp[n-1][n][i]);
    for(int i=2;i<=n;i++)   mmul(ans,qpow(i,mod-2));
    printf("%d\n",ans);
}