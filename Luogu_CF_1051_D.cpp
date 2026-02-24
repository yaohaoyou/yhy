#include<bits/stdc++.h>
using namespace std;
const int maxn=1010,mod=998244353;
int n,m;
int dp[maxn][maxn<<1][4];
#define rep(i) for(int i=0;i<4;i++)
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
int DP[4][4]={
    {0,1,1,1},
    {0,0,2,0},
    {0,2,0,0},
    {1,1,1,0}
};
int ans;
int main(){
    scanf("%d%d",&n,&m);
    // rep(x)dp[0][0][x]=1;
    dp[1][1][0]=1;dp[1][2][1]=1;dp[1][2][2]=1;dp[1][1][3]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=m;j++){
            rep(x) rep(y)
                if(j>=DP[x][y]) madd(dp[i][j][y],dp[i-1][j-DP[x][y]][x]);
            // rep(x)printf("dp[%d][%d][%d] = %d\n",i,j,x,dp[i][j][x]);
        }
    }
    rep(x) madd(ans,dp[n][m][x]);
    printf("%d\n",ans);
}