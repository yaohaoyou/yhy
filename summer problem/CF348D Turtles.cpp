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
const int maxn=3010,mod=1e9+7;
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
int n,m;
char s[maxn][maxn];
int dp[maxn][maxn];
inline int f(int x0,int y0,int x1,int y1){
    mems(dp,0);
    if(s[x0][y0]=='#')  return 0;
    dp[x0][y0]=1;
    for(int i=x0;i<=x1;i++){
        for(int j=y0;j<=y1;j++){
            if(i<x1&&s[i+1][j]=='.')    madd(dp[i+1][j],dp[i][j]);
            if(j<y1&&s[i][j+1]=='.')    madd(dp[i][j+1],dp[i][j]);
        }
    }
    return dp[x1][y1];
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%s",s[i]+1);
    int ans=imdel(immul(f(1,2,n-1,m),f(2,1,n,m-1)),immul(f(1,2,n,m-1),f(2,1,n-1,m)));
    printf("%d\n",ans);
}