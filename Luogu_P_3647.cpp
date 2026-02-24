#include<bits/stdc++.h>
#define eb emplace_back
using namespace std;
const int maxn=2e5+10;
int n;
int ans;
namespace Graph{
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
}
using namespace Graph;
int dp[maxn][2],f[maxn][2];  // dp[u][0/1] 表示 u  是/不是 蓝线的中点时的答案.f[u][0/1] 表示以 1 为根，不考虑 u 子树的答案
vector<int> c[maxn][2];
void dfs(int u,int fa){
    int mx=-2e9,se=-2e9,mid=0;
    dp[u][0]=dp[u][1]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs(t,u);
        dp[u][0]+=max(dp[t][0],dp[t][1]+e[i].w);
        int cost=-max(dp[t][0],dp[t][1]+e[i].w)+dp[t][0]+e[i].w;
        if(mx<cost){se=mx;mx=cost;mid=t;}
        else if(se<cost){se=cost;}
    }
    dp[u][1]=dp[u][0]+mx;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        c[u][0].eb(dp[u][0]-max(dp[t][0],dp[t][1]+e[i].w));
        if(t==mid)  c[u][1].eb(c[u][0].back()+se);
        else    c[u][1].eb(c[u][0].back()+mx);
    }
}
void solve(int u,int fa){
    // printf("u = %d,%d\n",u,f[u][0]);
    ans=max(ans,f[u][0]+dp[u][0]);
    int son=0;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        // printf("%d %d\n",c[u][0][son],c[u][1][son]);
        f[t][0]=max({f[u][0]+c[u][0][son],f[u][1]+c[u][0][son]+e[i].w,f[u][0]+c[u][1][son]+e[i].w});
        f[t][1]=f[u][0]+e[i].w+c[u][0][son];
        solve(t,u); 
        son++;
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1,u,v,w;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    f[1][1]=-2e9;
    dfs(1,0);solve(1,0);
    printf("%d\n",ans);
}