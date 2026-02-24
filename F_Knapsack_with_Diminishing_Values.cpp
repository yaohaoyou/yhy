#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=3010,B=3e4;
int n,m;
pii a[maxn];
ll dp[maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+n+1,[&](pii x,pii y){return 1.0*x.se/x.fi>1.0*y.se/y.fi;});
    mems(dp,-0x3f);dp[0]=0;
    for(int j=1;j<=n;j++){
        for(int i=m;i;i--){
            for(int k=1;k<=i/a[j].fi;k++){
                if(dp[i-k*a[j].fi]+1ll*(a[j].se-k)*k<dp[i]-B)  break;
                dp[i]=max(dp[i],dp[i-k*a[j].fi]+1ll*(a[j].se-k)*k);
            }
        }
        for(int i=1;i<=m;i++)   dp[i]=max(dp[i],dp[i-1]);
    }
    printf("%lld\n",dp[m]); 
}