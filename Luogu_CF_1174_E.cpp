#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e6+10,mod=1e9+7;
int n;
int dp[maxn][21][2];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
int main(){
    scanf("%d",&n);
    int l=log2(n);
    dp[1][l][0]=1;dp[1][l-1][1]=((1<<l-1)*3)<=n;
    auto cnt=[](int x){return n/x;};
    for(int i=2;i<=n;i++){
        for(int j=0;j<=l;j++){
            // gcd 不变
            madd(dp[i][j][0],immul(dp[i-1][j][0],cnt(1<<j)-i+1));
            madd(dp[i][j][1],immul(dp[i-1][j][1],cnt((1<<j)*3)-i+1));
            // gcd /= 2
            madd(dp[i][j][0],immul(dp[i-1][j+1][0],cnt(1<<j)-cnt(1<<j+1)));
            madd(dp[i][j][1],immul(dp[i-1][j+1][1],cnt((1<<j)*3)-cnt((1<<j+1)*3)));
            // gcd /= 3
            madd(dp[i][j][0],immul(dp[i-1][j][1],cnt(1<<j)-cnt((1<<j)*3)));
            // printf("dp[%d][%d] = %d : %d\n",i,j,dp[i][j][0],dp[i][j][1]);
        }
    }
    printf("%d\n",dp[n][0][0]);
}