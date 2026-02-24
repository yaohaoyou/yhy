#include<bits/stdc++.h>
#define ll long long
#define db double
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e5+10;
bool mem1;
int n;
int a[maxn];
ll dp[2][maxn];
bool mem2;
inline void getmx(ll &x,ll y){(x<y)&&(x=y);}
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    mems(dp[1],0);
    for(int i=1;i<n;i++){
        mems(dp[(i+1)&1],0);
        for(int j=0;j<i;j++){
            getmx(dp[(i+1)&1][j],dp[i&1][j]+(a[i]==a[i+1]?a[i]:0));
            getmx(dp[(i+1)&1][i],dp[i&1][j]+(a[i+1]==a[j]?a[i+1]:0));
        }
    }
    ll ans=0;
    for(int i=0;i<n;i++)    getmx(ans,dp[n&1][i]);
    printf("%lld\n",ans);
}
int main(){
    freopen("color.in","r",stdin);freopen("color.out","w",stdout);
    int T;
    scanf("%d",&T);while(T--)solve();
}
