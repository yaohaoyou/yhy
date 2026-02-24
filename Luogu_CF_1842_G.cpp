#include<bits/stdc++.h>
using namespace std;
const int maxn=5010,mod=1e9+7;
int n,m,v;
int dp[maxn][maxn],a[maxn];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
inline int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
int main(){
    scanf("%d%d%d",&n,&m,&v);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            madd(dp[i][j],immul(dp[i-1][j],a[i]));
            madd(dp[i][j],immul(immul(dp[i-1][j],j),v));
            if(j)   madd(dp[i][j],immul(immul(dp[i-1][j-1],i),immul(m-j+1,v)));
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++){madd(ans,immul(dp[n][i],qpow(qpow(n,i),mod-2)));}
    printf("%d\n",ans);
}