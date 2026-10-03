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
const int maxn=4e5+10;
int n;
int a[maxn];ll dp[maxn];
int main(){
    freopen("furioso.in","r",stdin);freopen("furioso.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    mems(dp,0x3f);
    dp[1]=0;
    for(int i=1;i<=n;i++){
        for(int j=i-1;j;j--){
            dp[i]=min(dp[i],dp[j]+1ll*a[i]*(i-j)*(i-j));
            if(a[j]<=a[i]) break;
        }
        for(int j=i+1;j<=n;j++){
            dp[j]=min(dp[j],dp[i]+1ll*a[i]*(j-i)*(j-i));
            if(a[j]<=a[i])  break;
        }
        printf("%lld ",dp[i]);
    }
}