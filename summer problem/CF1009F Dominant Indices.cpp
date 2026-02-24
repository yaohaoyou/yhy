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
const int maxn=1e6+10;
int n;
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
vector<int> dp[maxn];
int dep[maxn],son[maxn];
int ans[maxn];
void dfs(int u,int ft){
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        dfs(t,u);
        if(dep[t]>dep[son[u]])  son[u]=t;
    }
    if(son[u])  dep[u]=dep[son[u]]+1;
}
void dfs2(int u,int ft){
    // debug("%d %d\n",u,son[u]);
    pii res=pii(1,dep[u]);
    if(son[u]){
        dfs2(son[u],u);
        swap(dp[u],dp[son[u]]);
        ans[u]=ans[son[u]];
        // debug("# %d : %d %d %d %d\n",u,ans[u],dep[u]-ans[u],dep[u],dp[u][ans[u]]);
        res=max(res,pii(dp[u][ans[u]],ans[u]));
        dp[u].eb(0);
    }
    else    dp[u]=vector<int>(dep[u]+1);
    dp[u][dep[u]]=1;
    go(u,i){
        int t=e[i].to;
        if(t==ft||t==son[u])   continue;
        dfs2(t,u);
        for(int j=0;j<=dep[t];j++){
            // debug("(%d,%d) %d -> (%d,%d) %d\n",t,j,dp[t][j],u,j-dep[t]+dep[u]-1,dp[u][j-dep[t]+dep[u]-1]);
            dp[u][j-dep[t]+dep[u]-1]+=dp[t][j];
            res=max(res,pii(dp[u][j-dep[t]+dep[u]-1],j-dep[t]+dep[u]-1));
        }
    }
    ans[u]=res.se;
    // for(int i=0;i<=dep[u];i++)  debug("dp[%d][%d] = %d\n",u,dep[u]-i,dp[u][i]);
}
int main(){
    dep[0]=-1;
    scanf("%d",&n);
    for(int i=2;i<=n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);dfs2(1,0);
    for(int i=1;i<=n;i++)   printf("%d\n",dep[i]-ans[i]);
}