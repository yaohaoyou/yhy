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
const int maxn=1e5+10,logV=60;
int n,sum[2][maxn];
int dp[logV+5][maxn];
ll a[maxn];
inline void getmn(auto &x,auto y){(x>y)&&(x=y);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)   a[i]=a[n]-a[i];
    mems(dp,0x3f);dp[0][0]=0;
    for(int k=0;k<logV;k++){
        ll all=(1LL<<k)-1;
        sort(a+1,a+n+1,[&](ll x,ll y){return (x&all)>(y&all);});
        for(int i=1;i<=n;i++){
            sum[0][i]=sum[0][i-1];sum[1][i]=sum[1][i-1];
            sum[(a[i]>>k)&1][i]++;
        }
        for(int i=0;i<=n;i++){
            getmn(dp[k+1][sum[1][i]],dp[k][i]+sum[0][i]+sum[1][n]-sum[1][i]);
            getmn(dp[k+1][i+sum[1][n]-sum[1][i]],dp[k][i]+sum[1][i]+sum[0][n]-sum[0][i]);
        }
    }
    printf("%d\n",dp[logV][0]);
}