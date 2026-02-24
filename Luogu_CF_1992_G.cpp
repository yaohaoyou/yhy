#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e4+10,mod=1e9+7;
int n;
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
int fac[maxn],inv[maxn];
void init(){
    fac[0]=1;
    for(int i=1;i<=maxn-10;i++) fac[i]=immul(fac[i-1],i);
    inv[maxn-10]=qpow(fac[maxn-10],mod-2);
    for(int i=maxn-11;~i;i--)   inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y||x<0||y<0?0:1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void solve(){
    scanf("%d",&n);
    // for(int i=0;i<=n;i++){
    //     for(int j=1;j<=(n<<1|1);j++){
    //         // printf("dp[%d][%d] = %d\n",i,j,dp[i][j]);
    //         madd(dp[i+1][j],dp[i][j]);
    //         // if(i+1<=j)  madd(dp[i+1][j+2],dp[i][j]);
    //         if(i+1<=j+1)    madd(dp[i+1][j+2],dp[i][j]);
    //         else    madd(dp[i+1][j+1],dp[i][j]);
    //     }
    // }
    int ans=0;
    for(int i=1;i<=(n<<1|1);i++){  // mex=i
        for(int j=0;j<=n;j++){  // len=j;
            if(i-j-1<=j&&i-j-1+max(n-i,0)>=j){
                madd(ans,immul(i,immul(C(min(n,i-1),i-j-1),C(max(0,n-i),2*j-i+1))));
                // printf("res[%d][%d] = %d\n",i,j,C(min(n,i-1),j));
            }
        }
    }
    printf("%d\n",ans);
}
int main(){init();int T;scanf("%d",&T);while(T--)solve();}