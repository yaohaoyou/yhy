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
const int maxn=510,mod=998244353;
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
int a[maxn],b[maxn],c[maxn],pre[maxn],fac[maxn],C[maxn][maxn];
int dp[maxn][maxn][maxn];  // dp[i][j][k] 表示前 i 个人有 j 个没被录用，有 k 个 c>j
void init(){
    const int N=500;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    for(int i=0;i<=N;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j],C[i-1][j-1]);}
}
int main(){
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&c[i]),b[c[i]]++;
    pre[0]=b[0];
    for(int i=1;i<=n;i++)   pre[i]=pre[i-1]+b[i];
    dp[0][0][0]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=i;j++){
            for(int k=0;k<=i&&k<=pre[n]-pre[j];k++){
                if(!dp[i][j][k])    continue;
                if(!a[i+1]){
                    for(int l=0;l<=b[j+1]&&l<=k;l++){
                        // c>j+1,j++
                        madd(dp[i+1][j+1][k-l+1],1ull*dp[i][j][k]*C[k][l]%mod*C[b[j+1]][l]%mod*fac[l]%mod);
                        // printf("%d : %d %d %d\n",l,C[k][l],C[b[j+1]][l],fac[l]);
                        // c<=j+1,j++
                        if(pre[j+1]-i+k-l>0&&k-l<=n-pre[j+1])madd(dp[i+1][j+1][k-l],1ull*dp[i][j][k]*C[k][l]%mod*C[b[j+1]][l]%mod*fac[l]%mod*(pre[j+1]-i+k-l)%mod);
                    }
                }
                else{
                    // c>j
                    madd(dp[i+1][j][k+1],dp[i][j][k]);
                    // c<=j,j++
                    for(int l=0;l<=b[j+1]&&l<=k;l++){
                        if(pre[j]-i+k>0)    madd(dp[i+1][j+1][k-l],1ull*C[k][l]*C[b[j+1]][l]%mod*fac[l]%mod*dp[i][j][k]%mod*(pre[j]-i+k)%mod);
                    }
                }
                // printf("%d %d %d : %d\n",i,j,k,dp[i][j][k]);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=n-m;i++){
        madd(ans,immul(dp[n][i][n-pre[i]],fac[n-pre[i]]));
        // printf("%d %d : %d\n",i,n-pre[i],immul(dp[n][i][n-pre[i]],fac[n-pre[i]]));
    }
    printf("%d\n",ans);
}