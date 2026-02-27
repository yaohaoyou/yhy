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
#define NO exit(puts("-1")&0)
using namespace std;
const int maxn=5e5+10;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int n,m;
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn],dd[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
pii E[maxn];
vector<int> G[maxn],vec[maxn],GO[maxn];
vector<int> GS[maxn],rGS[maxn];
int col[maxn];
queue<int> q;
int tot,cscc;
int dfsn[maxn],low[maxn],scc[maxn];
bool instk[maxn],chk[maxn];
stack<int> stk;
void tarjan(int u){
    dfsn[u]=low[u]=++tot;
    instk[u]=true;stk.ep(u);
    go(u,i){
        if(!dfsn[t])    tarjan(t),gmn(low[u],low[t]);
        else if(instk[t])   gmn(low[u],dfsn[t]);
    }
    if(low[u]==dfsn[u]){
        cscc++;int p;
        do{
            p=stk.top();stk.pop();instk[p]=false;
            scc[p]=cscc;vec[cscc].eb(p);
        }while(p^u);
    }
}
inline void chg(int x,int y){if((~col[x])&&(col[x]^y))NO;col[x]=y;}
void dfs(int u,int ft){for(int t:GS[u])if(!~col[t])col[t]=col[u]^1,dfs(t,u);for(int t:rGS[u])if(!~col[t])col[t]=col[u]^1,dfs(t,u);}
queue<int> que;
void solve(int x){
    // if(x==10){
    //     for(int i:vec[x])   printf("col %d = %d\n",i,col[i]);puts("");
    //     for(int u:vec[x])for(auto t:GS[u])printf("%d %d\n",u,t);
    //     puts("");
    // }
    for(int i:vec[x])if(~col[i])que.ep(i);else if(!dd[i])col[i]=1,que.ep(i);
    while(!que.empty()){
        int u=que.front();que.pop();
        if(!col[u]){
            for(int t:GS[u])if((!~col[t])&&!(--dd[t]))que.ep(t),col[t]=1;
        }
        else{
            for(int t:GS[u]){
                if(!~col[t]) que.ep(t);
                col[t]=0;
            }
            for(int t:rGS[u]){
                if(!~col[t]) que.ep(t);
                col[t]=0;
            }
        }
    }
    for(int i:vec[x])if(!~col[i])col[i]=1,dfs(i,0);
    for(int u:vec[x])if(col[u])for(int t:GO[u])col[t]=0;
    // if(x==10){
    //     for(int i:vec[x])   printf("col %d = %d\n",i,col[i]);puts("");
    // }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);swap(u,v);add(u,v);E[i]=pii(u,v);}
    for(int i=1;i<=n;i++)if(!dfsn[i])tarjan(i);
    // for(int i=1;i<=n;i++)   debug("%d ",scc[i]);puts("");
    for(int i=1;i<=m;i++){
        int u=E[i].fi,v=E[i].se;
        if(scc[u]==scc[v])  GS[u].eb(v),dd[v]++,rGS[v].eb(u);
        else    G[scc[u]].eb(scc[v]),deg[scc[v]]++,GO[u].eb(v);
    }
    mems(col,-1);
    for(int i=1;i<=cscc;i++)if(!deg[i])q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        solve(u);
        for(int t:G[u])if(!(--deg[t]))q.ep(t);
    }
    // debug("col[%d] = %d\n",81046,col[81046]);
    for(int i=1;i<=m;i++){
        int u=E[i].fi,v=E[i].se;
        // if(col[u]&&col[v])  debug("(%d,%d)\n",scc[u],scc[v]);
        // if(v==81046)    debug("! %d %d\n",col[v],col[u]);
        if(!col[v]&&col[u]) chk[v]=true;
    }
    // assert(!count(col+1,col+n+1,-1));
    // for(int i=1;i<=m;i++)if(!col[i]&&!chk[i])debug("i = %d %d\n",i,scc[i]);
    printf("%d\n",count(col+1,col+n+1,1));
    for(int i=1;i<=n;i++)if(col[i])printf("%d ",i);puts("");
}