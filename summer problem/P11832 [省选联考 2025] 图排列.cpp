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
const int maxn=1e5+10;
int n,m;
int tot;
vector<int> son[maxn];
int mn[maxn],bel[maxn];
int dfsn[maxn],low[maxn];
int up[maxn][2],U[maxn];
int dp[maxn][2];  // dp[u][0/1] 表示 u 是/否在父亲中最后一个被选，能到达的最小值
vector<pii> out[maxn][2];
queue<int> vq[maxn];
priority_queue<pii,vector<pii>,greater<pii>> q;
stack<int> stk;
void rebuild(){for(int i=1;i<=n;i++)son[i].clear();}
pii cmn(int u,int v){
    if(!U[v])  return pii(min(dp[v][0],dp[v][1]),v);
    else if(U[v]==1){
        if(low[up[v][0]]==dfsn[u]) return pii(dp[v][1],v);
        else    return pii(dp[v][0],v);
    }
    else{
        int x=up[v][0],y=up[v][1];
        if(low[x]==low[y])  return pii(min(dp[v][0],dp[v][1]),v);
        else if(low[x]<low[y])    return pii(dp[v][0],v);
        else    return pii(dp[v][1],v);
    }
}
pii cmx(int u,int v){
    if(!U[v])  return pii(max(dp[v][0],dp[v][1]),v);
    else if(U[v]==1){
        if(low[up[v][0]]==dfsn[u]) return pii(dp[v][0],v);
        else    return pii(dp[v][1],v);
    }
    else{
        int x=up[v][0],y=up[v][1];
        if(low[x]==low[y])  return pii(max(dp[v][0],dp[v][1]),v);
        else if(low[x]<low[y])    return pii(dp[v][1],v);
        else    return pii(dp[v][0],v);
    }
}
void dfs(int u,int ft){
    dp[u][0]=dp[u][1]=u;
    mn[u]=u;dfsn[u]=low[u]=++tot;
    vector<pii> tmp;tmp.clear();
    for(int t:son[u]){
        if(t==ft)   continue;
        if(!dfsn[t]){
            dfs(t,u);
            if(low[t]<dfsn[u])  up[u][U[u]++]=t;
            else tmp.eb(min(dp[t][0],dp[t][1]),t);
            low[u]=min(low[u],low[t]);
        }
        else    low[u]=min(low[u],dfsn[t]);
    }
    tmp.eb(u,u);
    sort(tmp.begin(),tmp.end());
    if(U[u]>=1) out[u][0].eb(cmn(u,up[u][0]));
    if(U[u]>=2) out[u][1].eb(cmn(u,up[u][1]));
    for(pii i:tmp)  out[u][0].eb(i),out[u][1].eb(i);
    if(U[u]>=2) out[u][0].eb(cmx(u,up[u][1]));
    if(U[u]>=1) out[u][1].eb(cmx(u,up[u][0]));
    dp[u][0]=out[u][0].front().fi;dp[u][1]=out[u][1].front().fi;
}
void dfs2(int u,int ft,int rt){
    bel[u]=rt;
    for(pii p:out[u][0]){
        int t=p.se;
        if(t==ft)   continue;
        if(t==u){printf("%d ",u);continue;}
        dfs2(t,u,rt);
    }
}
void matt(int _cases){
    rebuild();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);son[u].eb(v);son[v].eb(u);}
    fill(mn+1,mn+n+1,0);
    // for(int i=1;i<=n;i++)if(!mn[i])dfs(i,0),dfs2(i,0,i),q.ep(vq[i].front(),i);
    // while(!q.empty()||!stk.empty()){
    //     int u=q.empty()?0:q.top().se;
    //     if(!q.empty()&&(stk.empty()||vq[u].front()<vq[stk.top()].front())){
    //         q.pop();
    //         printf("%d ",vq[u].front());vq[u].pop();
    //         if(!vq[u].empty())  stk.ep(u);
    //     }
    //     else{
    //         u=stk.top();printf("%d ",vq[u].front());vq[u].pop();
    //         if(vq[u].empty())   stk.pop();
    //     }
    // }
    dfs(1,0);dfs2(1,0,1);puts("");
}
int main(){int T;scanf("%*d%d",&T);for(int i=1;i<=T;i++)matt(i);}