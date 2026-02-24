#pragma GCC optimize(2,3,"Ofast","inline")
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
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m;
int dp[maxn][maxn][2],sx[maxn][maxn],sy[maxn][maxn],ans[maxn][maxn];  // dp[i][j] 表示有 i 个 a 和 j 个 b，最后一个是 a/b 的方案数(i<=j)
void matt(){scanf("%d%d",&n,&m);if(n>m)swap(n,m);printf("%d\n",ans[n][m]);}
int main(){
    n=2000;
    for(int k=1;k<=n/2;k++){
        int lim=min(n,n*2/k);
        for(int i=0;i<=k;i++){
            sx[i][0]=sy[0][i]=dp[i][0][0]=dp[0][i][1]=1;
            for(int j=1;j<=lim;j++)   sx[i][j]=sy[j][i]=j+1;
        }
        for(int i=1;i<=lim;i++){
            for(int j=1;j<=n;j++){
                // if((j+i)/(i+1)<k)break;
                // dp[i][j][0]=dp[i][j][1]=0;
                // for(int l=max(0,i-k);l<i;l++) madd(dp[i][j][0],dp[l][j][1]);
                // for(int l=max(0,j-k);l<j;l++) madd(dp[i][j][1],dp[i][l][0]);
                dp[i][j][0]=imdel(sy[i-1][j],(i-k>0)?sy[i-k-1][j]:0);
                dp[i][j][1]=imdel(sx[i][j-1],(j-k>0)?sx[i][j-k-1]:0);
                // for(int l=max(j-k,i);l<j;l++) madd(dp[i][j][1],dp[i][l][0]);
                if(k==(j+i)/(i+1))  ans[i][j]=imadd(dp[i][j][0],dp[i][j][1]);
                // printf("%d %d %d : %d %d\n",k,i,j,dp[i][j][0],dp[i][j][1]);
                sx[i][j]=imadd(sx[i][j-1],dp[i][j][0]);sy[i][j]=imadd(sy[i-1][j],dp[i][j][1]);
            }
        }
    }
    int T;scanf("%d",&T);while(T--)matt();
}