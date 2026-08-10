#include<map>
#include<math.h>
#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#include<unordered_map>
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
const int maxn=510,mod=999911659;
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
int p;pii r;
unordered_map<int,int> mp;
int dp[maxn][10][maxn];  // dp[i][j][k] now mod p=i,j 个 11..11,sum mod p=k
ll cnt[maxn];int inv[10],w[maxn][10];
inline int C(ll x,int y){
    if(x<y) return 0;
    x%=mod;
    int res=1;
    for(int i=1;i<=y;i++)   mmul(res,x-i+1);
    for(int i=1;i<=y;i++)   mmul(res,inv[i]);
    return res;
}
int solve(ll n){
    mp.clear();r=pii(0,0);
    {
        int x=1,i=1;
        while(i<=n){
            if(mp.find(x)!=mp.end()){
                r=pii(mp[x],i-1);
                break;
            }
            mp[x]=i++;
            x=(x*10+1)%p;
        }
        if(!r.fi)   r.fi=n+1;
    }
    mems(dp,0);mems(cnt,0);
    int x=1;
    for(int i=1;i<r.fi;i++){cnt[x]++;x=(x*10+1)%p;}
    for(int i=r.fi;i<=r.se;i++){
        ll xx=n-r.fi+1,yy=r.se-r.fi+1;
        cnt[x]+=xx/yy+(xx%yy>=i-r.fi+1);
        x=(x*10+1)%p;
    }
    // printf("n = %d,r = (%d,%d)\n",n,r.fi,r.se);
    // for(int i=0;i<=p;i++)   printf("%d ",cnt[i]);puts("");
    for(int i=0;i<=p;i++)for(int j=1;j<=9;j++)w[i][j]=C(cnt[i]+j-1,j);
    dp[0][0][0]=1;
    for(int i=0;i<=p;i++){
        for(int j=0;j<=9;j++){
            for(int k=0;k<=p;k++){
                madd(dp[i+1][j][k],dp[i][j][k]);
                for(int l=1;l+j<=9;l++)
                    madd(dp[i+1][l+j][(k+l*i)%p],immul(dp[i][j][k],w[i][l]));
                // if(dp[i][j][k]) printf("%d %d %d : %d\n",i,j,k,dp[i][j][k]);
            }
        }
    }
    int ret=0;
    for(int i=1;i<=9;i++)   madd(ret,dp[p+1][i][0]);
    return ret;
}
int main(){
    for(int i=1;i<=9;i++)   inv[i]=qpow(i,mod-2);
    ll n;
    scanf("%lld%d",&n,&p);
    // printf("%d\n",solve(n));
    printf("%d\n",imdel(solve(n),solve(n-1)));
}