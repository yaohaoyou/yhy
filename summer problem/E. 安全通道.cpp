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
const int maxn=2.5e5+10;
int n;
int a[maxn];
bool mk[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int dp[maxn][2];
void dfs(int u,int ft){
    dp[u][0]=0;dp[u][1]=1;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
        dp[u][0]+=max(dp[t][0],dp[t][1]);
        dp[u][1]+=dp[t][0];
    }
}
void dfs2(int u,int ft){
    if(ft){
        int f0=dp[ft][0]-max(dp[u][0],dp[u][1]),f1=dp[ft][1]-dp[u][0];
        dp[u][0]+=max(f0,f1);dp[u][1]+=f0;
    }
    go(u,i){
        if(t==ft)   continue;
        dfs2(t,u);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    ll ans=0;int cnt=0,mx=0;
    dfs(1,0);mx=max(dp[1][1],dp[1][0]);
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        mk[i]=dp[i][0]==mx;
        cnt+=mk[i];
        if(mk[i])   ans+=n-1-deg[i];
    }
    ans-=1ll*cnt*(cnt-1)/2;
    for(int u=1;u<=n;u++){
        if(!mk[u])  continue;
        go(u,i)if(t>u&&mk[t])ans++;
    }
    ans+=n-1;
    printf("%lld\n",ans);
}