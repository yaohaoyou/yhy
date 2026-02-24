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
const int maxn=4010;
int n,m;
pii a[maxn];
int c[maxn];
int dp[maxn][maxn];  // dp[i][j] 表示已经选了攻击性为 [i,n]，其中选了 j 个 i  的答案
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=n;i;i--)   scanf("%d",&a[i].fi);
    for(int i=n;i;i--)   scanf("%d",&a[i].se);
    m+=n;
    for(int i=1;i<=m;i++)   scanf("%d",&c[i]);
    mems(dp,-0x3f);
    for(int i=0;i<=m;i++) dp[i][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=n;j;j--)   gmx(dp[a[i].fi][j],dp[a[i].fi][j-1]-a[i].se+c[a[i].fi]);
        for(int j=a[i].fi;j<=m;j++){
            for(int k=0;k<=n>>(j-a[i].fi);k++)   gmx(dp[j+1][k/2],dp[j][k]+k/2*c[j+1]);
        }
    }
    printf("%d\n",dp[m][0]);
}