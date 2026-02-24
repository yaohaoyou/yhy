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
int n,m,T;
int a[maxn],b[maxn];
ll dp[maxn];
void matt(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        int mx=0;ll res=0;
        for(int j=i;j;j--){
            mx=max(mx,a[j]);res+=b[j];
            dp[i]=max(dp[i],dp[j-1]+res-1ll*mx*m);
        }
    }
    printf("%lld\n",dp[n]);
}
int main(){scanf("%d",&T);while(T--)matt();}