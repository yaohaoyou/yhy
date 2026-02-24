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
const int maxn=55,mod=998244353;
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
int n;
int C[maxn][maxn];
int f[maxn][maxn][maxn],dp[maxn*maxn][maxn*maxn];
// f[i][j][k] 表示前 i 个数填了 j 个位置，出现次数最多的出现了 k 次 的方案数
// dp[i][j] 表示前 i 个位置选出的和为 j 的方案数
void init(){
    const int N=50;
    for(int i=0;i<=N;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}
}
int main(){
    init();
    scanf("%d",&n);
    f[0][0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=n;k++){
                for(int l=0;j+l<=n;l++) madd(f[i+1][j+l][max(k,l)],immul(f[i][j][k],C[n-j][l]));
            }
        }
    }
    dp[0][0]=1;
    for(int i=0;i<n*n;i++){
        for(int j=i;j<=n*n+n;j++){
            for(int k=1;k<=n;k++)madd(dp[i+1][min(n*n+n,j+k)],immul(dp[i][j],f[n][n][k]));
        }
    }
    // debug("%d\n",qpow(n,n*n*n));
    printf("%d\n",imdel(qpow(n,n*n*n),dp[n*n][n*n+n]));
}