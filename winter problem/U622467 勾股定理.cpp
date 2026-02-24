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
const int maxn=4e6+10,mod=998244353;
int n;
int dp[maxn];
bitset<maxn> f[5];
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
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
int main(){
    scanf("%d",&n);
    mems(dp,0x3f);dp[0]=0;
    // for(int i=1;i<=n;i++)for(int j=1;j*j<=i;j++)gmn(dp[i],dp[i-j*j]+1);
    f[0].set(0);
    for(int i=1;i<=4;i++)
        for(int j=1;j*j<=n;j++) f[i]|=f[i-1]<<(j*j);
    int ans=0,pq=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=4;j++)if(f[j][i]){dp[i]=j;break;}
        if(dp[i]^1) dp[i]=dp[i]*2-1;
        madd(ans,immul(dp[i],pq));
        mmul(pq,218105633);
    }
    printf("%d\n",ans);
}