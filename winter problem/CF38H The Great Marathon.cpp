#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=60;
int n,m,gL,gR,sL,sR;
int dis[maxn][maxn],rnk[maxn][maxn],mn[maxn],mx[maxn];
ll ans;
vector<piii> vec;
ll dp[maxn][maxn][maxn];  // dp[i][j][k] 表示前 i 个人有 j 个 au，k 个 cu
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
void slv(int u,int v,int au,int cu){
    if(au>=cu)  return;
    mems(dp,0);dp[0][0][0]=1;
    for(int i=1;i<=n;i++){
        if(i==u){
            for(int j=1;j<=i;j++)for(int k=0;j+k<=i;k++)dp[i][j][k]=dp[i-1][j-1][k];
            continue;
        }
        if(i==v){
            for(int j=0;j<=i;j++)for(int k=1;j+k<=i;k++)dp[i][j][k]=dp[i-1][j][k-1];
            continue;
        }
        bool iag=false;
        for(int j=1;j<=n;j++)if(rnk[i][j]>au&&rnk[i][j]<cu){iag=true;break;}
        for(int j=0;j<=i;j++){
            for(int k=0;j+k<=i;k++){
                if(mn[i]<=au&&j)   dp[i][j][k]=dp[i-1][j-1][k];
                if(iag) dp[i][j][k]+=dp[i-1][j][k];
                if(mx[i]>=cu&&k)    dp[i][j][k]+=dp[i-1][j][k-1];
            }
        }
    }
    for(int i=gL;i<=gR;i++)for(int j=sL;j<=sR;j++)ans+=dp[n][i][n-i-j];
}
int main(){
    scanf("%d%d",&n,&m);
    mems(dis,0x3f);for(int i=1;i<=n;i++)dis[i][i]=0;
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);gmn(dis[u][v],w);gmn(dis[v][u],w);}
    scanf("%d%d%d%d",&gL,&gR,&sL,&sR);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)gmn(dis[j][k],dis[j][i]+dis[i][k]);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)vec.eb(dis[i][j],pii(i,j));
    sort(vec.begin(),vec.end());
    for(int i=0;i<n*n;i++)rnk[vec[i].se.fi][vec[i].se.se]=i+1;
    for(int i=1;i<=n;i++){
        mn[i]=1e9;mx[i]=0;
        for(int j=1;j<=n;j++)if(i^j)gmn(mn[i],rnk[i][j]),gmx(mx[i],rnk[i][j]);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)if(i^j)slv(i,j,mn[i],mx[j]);
    printf("%lld\n",ans);
}