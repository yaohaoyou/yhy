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
const int maxn=5e5+10;
int n;
int a[maxn],b[maxn];
ll dp[maxn][2];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int main(){
    freopen("balance.in","r",stdin);freopen("balance.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    for(int i=2;i<=n;i++){
        dp[i][0]=min(dp[i-1][0]+abs(a[i]-a[i-1]),dp[i-1][1]+abs(a[i]-b[i-1]));
        dp[i][1]=min(dp[i-1][0]+abs(b[i]-a[i-1]),dp[i-1][1]+abs(b[i]-b[i-1]));
    }
    printf("%lld\n",min(dp[n][0],dp[n][1]));
}