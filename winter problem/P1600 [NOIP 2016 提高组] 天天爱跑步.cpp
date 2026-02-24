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
const int maxn=3e5+10;
int n,m;
int a[maxn];
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
int tot;
int dfn[maxn],dep[maxn],fa[maxn],ans[maxn];
vector<int> ins[2][maxn],era[2][maxn];
unordered_map<int,int> mp[2][maxn];
int tag[2][maxn];
namespace st_LCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using st_LCA::LCA;
void dfs(int u,int ft){
    fa[u]=st_LCA::st[0][dfn[u]=++tot]=ft;dep[u]=dep[ft]+1;
    go(u,i)if(t^ft)dfs(t,u);
}
void dfs1(int u,int ft){
    go(u,_){
        if(t==ft)   continue;
        dfs1(t,u);
        if(mp[0][u].size()<mp[0][t].size()) mp[0][u].swap(mp[0][t]),swap(tag[0][u],tag[0][t]);
        for(auto [i,j]:mp[0][t])    mp[0][u][i+tag[0][t]-tag[0][u]]+=j;
        if(mp[1][u].size()<mp[1][t].size()) mp[1][u].swap(mp[1][t]),swap(tag[1][u],tag[1][t]);
        for(auto [i,j]:mp[1][t])    mp[1][u][i+tag[1][t]-tag[1][u]]+=j;
    }
    tag[0][u]++;tag[1][u]--;
    for(int i:ins[0][u])mp[0][u][i-tag[0][u]]++;
    for(int i:ins[1][u])mp[1][u][i-tag[1][u]]++;
    for(int i:era[0][u])mp[0][u][i-tag[0][u]]--;
    for(int i:era[1][u])mp[1][u][i-tag[1][u]]--;
    // for(auto [i,j]:mp[0][u])    printf("mp[0][%d][%d] = %d\n",u,i+tag[0][u],j);
    // for(auto [i,j]:mp[1][u])    printf("mp[1][%d][%d] = %d\n",u,i+tag[1][u],j);
    ans[u]=mp[0][u][a[u]-tag[0][u]]+mp[1][u][a[u]-tag[1][u]];
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    dfs(1,0);st_LCA::build();
    for(int i=1;i<=m;i++){
        int s,t;scanf("%d%d",&s,&t);
        int lc=LCA(s,t),dis=dep[s]+dep[t]-(dep[lc]<<1);
        ins[0][s].eb(0);era[0][fa[lc]].eb(dep[s]-dep[fa[lc]]);
        ins[1][t].eb(dis);era[1][lc].eb(dis+dep[lc]-dep[t]);
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);
}