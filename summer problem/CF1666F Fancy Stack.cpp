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
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn],b[maxn],buc[maxn],dp[maxn][maxn];
int sum[maxn][maxn];
void matt(){
    for(int i=1;i<=n;i++)buc[i]=0;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=sum[i][j]=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        buc[a[i]]++;
        b[i]=i-buc[a[i]];
    }
    for(int i=1;i<=n;i++)   dp[i][1]=b[i];
    for(int i=1;i<=n;i++)   sum[1][i]=imadd(sum[1][i-1],immul(dp[i][1],b[i]-1));
    for(int j=2;j<=n/2;j++){
        for(int i=j*2;i<=n;i++){
            int l=upper_bound(b+1,b+n+1,2*(j-1)-1)-b,r=lower_bound(a+1,a+n+1,a[i])-a-1;
            if(l<=r&&r<=n)  madd(dp[i][j],imdel(sum[j-1][r],sum[j-1][l-1]));
            // for(int k=1;k<i;k++)
            //     if(a[k]<a[i]&&b[k]-2*(j-1)+1>0)   madd(dp[i][j],immul(dp[k][j-1],b[k]-2*(j-1)+1));
            sum[j][i]=imadd(sum[j][i-1],immul(dp[i][j],b[i]-2*j+1));
        }
    }
    for(int i=1;i<=n;i++){
        int fac=1;
        for(int j=1;j<=buc[i];j++)   mmul(fac,j);
        mmul(dp[n][n/2],qpow(fac,mod-2));
    }
    printf("%d\n",dp[n][n/2]);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}