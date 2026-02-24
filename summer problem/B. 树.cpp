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
const int maxn=5e3+10;
const ll INF=1e18;
int n;
int a[maxn],b[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
ll dp[maxn][maxn];  // dp[u][i] 表示 p_u=i 的最大价值
void dfs(int u,int ft){
    mems(dp[u],-0x3f);dp[u][0]=0;
    for(int j=1;j<=n;j++)   dp[u][j]=b[j-1]-a[u];
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
        for(int j=0;j<=n;j++)   dp[u][j]+=max({j?dp[t][j-1]:-INF,dp[t][j],dp[t][j+1]});
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=0;i<n;i++)    scanf("%d",&b[i]);
    for(int i=1,u,v;i<n;i++){scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    ll ans=0;
    for(int i=0;i<=n;i++)   ans=max(ans,dp[1][i]);
    printf("%lld\n",ans);
}