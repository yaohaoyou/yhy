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
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,l,r;
int a[maxn],b[maxn];
unordered_map<int,int> dp[2][maxn];  // dp[i][j][k] 表示 -a 到 i,+b 到 j,当前答案为 k 的方案数
int main(){
    scanf("%d%d%d",&n,&l,&r);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int V=0;
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]),V+=b[i];
    // for(int i=l;i<=r;i++)   dp[n][n][i]=1;
    dp[0][0][0]=1;
    // for(int i=n;i;i--){
    //     for(int j=1;j<=i;j++){
    //         for(int k=b[j];k<=V;k++)    madd(dp[i][j-1][k-b[j]],dp[i][j][k]);
    //         for(int k=0;k<=a[i];k++)    madd(dp[i-1][j][k],dp[i][j][0]);
    //     }
    // }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++)   dp[(i+1)&1][j].clear();
        for(int j=0;j<=i;j++){
            for(auto [k,l]:dp[i&1][j]){
                madd(dp[(i+1)&1][j][max(0,k-a[i+1])],l);
                if(j<i&&k+b[j+1]<=V)madd(dp[i&1][j+1][k+b[j+1]],l);
            }
        }
    }
    int ans=0;
    for(int i=l;i<=r;i++)   madd(ans,dp[n&1][n][i]);
    printf("%d\n",ans);
}
/*
0 0 0
1 0 0
1 1 924

*/