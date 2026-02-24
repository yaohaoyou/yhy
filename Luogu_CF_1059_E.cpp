#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e5+10;
int n,l;
ll s;
ll a[maxn];
namespace Graph{
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
// nex[i][u] 表示从 u 往上跳 2^i-1 步经过的点的点权和
// f[i][u] 表示从 u 往上跳 2^i 后到达的点
ll nex[20][maxn],f[20][maxn];
// dp[i] 是题解中的 f[i]
int dp[maxn],g[maxn];
int up[maxn];
void dfs1(int u,int fa){
    f[0][u]=fa;nex[0][u]=a[u];
    go(u,i){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs1(t,u);
    }
}
void dfs2(int u,int fa){
    go(u,i){    
        int t=e[i].to;
        if(t==fa)   continue;
        dfs2(t,u);
        g[u]=max(g[u],g[t]-1);
        dp[u]+=dp[t];
    }
    if(!g[u])  dp[u]++,g[u]=up[u];
    printf("dp[%d] = %d : %d\n",u,dp[u],g[u]);
}
int main(){
    scanf("%d%d%lld",&n,&l,&s);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        // 判无解
        if(a[i]>s)  return puts("-1")&0;
    }
    for(int i=2;i<=n;i++){
        int x;scanf("%d",&x);
        adde(i,x);
    }
    // 将不存在的节点设极大值，防止倍增跳到 0
    a[0]=1e18;
    dfs1(1,0);
    // 树上倍增
    for(int i=1;i<20;i++){
        for(int j=1;j<=n;j++){
            nex[i][j]=nex[i-1][j]+nex[i-1][f[i-1][j]];
            f[i][j]=f[i-1][f[i-1][j]];
        }
    }
    for(int i=1;i<=n;i++){
        int s1=0,p=i;
        ll s2=0;
        for(int j=19;~j;j--){
            if(s1+(1<<j)>l) continue;
            if(s2+nex[j][p]>s)  continue;
            s1+=(1<<j);s2+=nex[j][p];
            p=f[j][p];
        }
        up[i]=s1;
    }

    // 树形 DP
    dfs2(1,0);
    printf("%d\n",dp[1]);
}