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
const int maxn=1e4+10,maxv=50*maxn;
int n;
int a[maxn],c[maxn];
int dp[2][maxv];  // dp[i][j] 表示当前已经放了 i 个 c，a 的和为 j 的 a[i]^2 的最小值
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmn(ll &x,ll y){(x>y)&&(x=y);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),c[i]=a[i]-a[i-1];
    sort(c+2,c+n+1);
    mems(dp,0x3f);dp[1][0]=0;
    const int inf=dp[0][0];
    int mx=0,s=0;
    for(int i=1;i<n;i++){
        // for(int j=0;j<=mx;j++)  printf("%d %d : %d\n",i,j,dp[i][j]);
        mems(dp[(i+1)&1],0x3f);
        s+=c[i+1];
        int nmx=0;
        for(int j=s-c[i+1];j<=mx;j++){
            if(dp[i&1][j]==inf)   continue;
            gmn(dp[(i+1)&1][j+i*c[i+1]],dp[i&1][j]+2*j*c[i+1]+i*c[i+1]*c[i+1]);
            nmx=max(nmx,j+i*c[i+1]);
            gmn(dp[(i+1)&1][j+s],dp[i&1][j]+s*s);
            nmx=max(nmx,j+s);
        }
        mx=nmx;
    }
    // for(int j=0;j<=mx;j++)  printf("%d %d : %d\n",n,j,dp[n][j]);
    ll ans=1e18;
    for(int i=0;i<=mx;i++){
        int x=i+c[1]*n;
        ll w=1ll*n*(dp[n&1][i]+2*i*c[1]+n*c[1]*c[1])-1ll*x*x;
        gmn(ans,w);
    }
    printf("%lld\n",ans);
}