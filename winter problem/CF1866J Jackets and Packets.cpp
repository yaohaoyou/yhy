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
const int maxn=410;
unordered_map<int,int> mp;
int n,x,y;
int a[maxn],b[maxn],nxt[maxn];
ll f[maxn][maxn],g[maxn][maxn],dp[maxn][maxn];  // dp[l][r] 表示移除 [l,r] 的最小代价，f[l][r] 表示
inline void gmn(ll &x,ll y){(x>y)&&(x=y);}
inline void gmx(ll &x,ll y){(x<y)&&(x=y);}
int main(){
    scanf("%d%d%d",&n,&x,&y);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    {
        int m=0;
        for(int i=1;i<=n;i++){
            int j=i;while(j<=n&&a[i]==a[j])j++;j--;
            a[++m]=a[i];b[m]=j-i+1;
            i=j;
        }
        n=m;
    }
    for(int i=n;i;i--){nxt[i]=mp[a[i]];mp[a[i]]=i;}
    mems(dp,0x3f);mems(f,0x3f);mems(g,0x3f);
    for(int i=1;i<=n+1;i++)   dp[i][i-1]=f[i][i-1]=g[i][i-1]=0,f[i][i]=1ll*y*b[i],g[i][i]=2ll*y*b[i];
    for(int len=1;len<=n;len++){
        for(int l=1,r=len;r<=n;l++,r++){
            gmn(dp[l][r],dp[l][r-1]+x);
            int p=l;
            while(p&&p<=r){
                gmn(dp[l][r],f[l][p]+dp[p+1][r]+x);
                gmn(dp[l][r],g[l][p]-2ll*y*b[p]+x+dp[p+1][r]);
                if(a[l]==a[r]){
                    gmn(f[l][r],f[l][p]+dp[p+1][r-1]+1ll*y*b[r]);
                    gmn(g[l][r],g[l][p]+dp[p+1][r-1]+2ll*y*b[r]);
                }
                p=nxt[p];
            }
            // printf("[%d,%d] : %d %d %d\n",l,r,dp[l][r],f[l][r],g[l][r]);
        }
    }
    printf("%lld\n",dp[1][n]);
}