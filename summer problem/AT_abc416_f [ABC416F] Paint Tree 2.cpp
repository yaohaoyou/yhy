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
const int maxn=2e5+10;
int n,k;
int a[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
inline void getmx(auto &x,auto y){(x<y)&&(x=y);}
ll dp[maxn][7][3];
void dfs(int u,int ft){
    ll f[7][3];
    dp[u][0][0]=0;dp[u][1][1]=a[u];
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        dfs(t,u);
        memc(f,dp[u]);
        for(int i=0;i<=k;i++){
            for(int j=0;i+j<=k;j++){
                ll mx=max({dp[t][j][0],dp[t][j][1],dp[t][j][2]});
                getmx(dp[u][i+j][0],f[i][0]+mx);
                getmx(dp[u][i+j][1],f[i][1]+mx);
                getmx(dp[u][i+j][1],f[i][0]+dp[t][j][1]+a[u]);
                getmx(dp[u][i+j][2],max(f[i][1],f[i+1][1])+dp[t][j][1]);
                getmx(dp[u][i+j][2],f[i][1]+max(dp[t][j][1],dp[t][j+1][1]));
                getmx(dp[u][i+j][2],f[i][2]+mx);
            }
        }
    }
    // for(int i=0;i<=k;i++)   printf("%d %d : %d %d %d\n",u,i,dp[u][i][0],dp[u][i][1],dp[u][i][2]);
}
int main(){
    mems(dp,-0x3f);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    ll ans=0;
    for(int i=0;i<=k;i++)   ans=max(ans,max({dp[1][i][0],dp[1][i][1],dp[1][i][2]}));
    printf("%lld\n",ans);
}