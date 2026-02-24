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
const int maxn=1010,mod=998244353;
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
int n,k;
int a[maxn],dp[2][maxn],s[2][maxn];
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    int ans=0;
    a[0]=-1e9;
    for(int x=1;x<=a[n]/(k-1);x++){
        dp[0][0]=1;
        for(int i=0;i<=n;i++)   s[0][i]=1;
        for(int i=1;i<=k;i++){
            mems(dp[i&1],0);s[i&1][0]=0;
            for(int j=1,p=0;j<=n;j++){
                while(p+1<j&&a[j]-a[p+1]>=x)    p++;
                // for(int l=0;l<=p;l++)   madd(dp[i&1][j],dp[(i-1)&1][l]);
                dp[i&1][j]=s[(i-1)&1][p];
                s[i&1][j]=imadd(s[i&1][j-1],dp[i&1][j]);
            }
        }
        for(int i=1;i<=n;i++)   madd(ans,dp[k&1][i]);
    }
    printf("%d\n",ans);
}