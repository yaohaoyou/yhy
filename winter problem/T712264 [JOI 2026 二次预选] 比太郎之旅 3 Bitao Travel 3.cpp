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
const int maxn=3e6+10;
int n,m;
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
int cscc;
vector<int> son[2][maxn],G[maxn];
int scc[maxn];
unordered_set<int> ss[maxn];
int deg[maxn];
int tot;
int dfsn[maxn],low[maxn];
bool ins[maxn];
stack<int> stk;
int F[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
void tarjan(int u){
    dfsn[u]=low[u]=++tot;
    stk.ep(u);ins[u]=true;
    go(u,i){
        if(!dfsn[t]){
            tarjan(t);
            gmn(low[u],low[t]);
        }
        else if(ins[t]) gmn(low[u],dfsn[t]);
    }
    if(low[u]==dfsn[u]){
        cscc++;
        int p=0;
        do{
            p=stk.top();stk.pop();
            ins[p]=false;scc[p]=cscc;
        }while(p^u);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);son[u<v][u].eb(v);son[v<u][v].eb(u);}
    for(int u=1;u<=n;u++){
        for(int x:son[1][u])for(int y:son[0][x])add(u,y);
    }
    for(int i=1;i<=n;i++)if(!dfsn[i])tarjan(i);
    for(int u=1;u<=n;u++){
        go(u,i)if(scc[t]^scc[u])G[scc[t]].eb(scc[u]),deg[scc[u]]++,assert(0);
        ss[scc[u]].ep(u);
        for(int t:son[1][u])ss[scc[u]].ep(t);
    }
    queue<int> q;
    for(int i=1;i<=cscc;i++)F[i]=ss[i].size();
    for(int i=1;i<=cscc;i++)if(!deg[i])q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int t:G[u]){
            F[u]+=F[t];
            if(!(--deg[t]))q.ep(t);
        }
    }
    for(int i=1;i<=n;i++)   printf("%d\n",n-F[scc[i]]);
}