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
const int maxn=2e6+10;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int n,m;
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
inline int id(int x,int o){return x+o*n;}
int tot,cscc;
int dfsn[maxn],low[maxn],scc[maxn];
bool instk[maxn];
stack<int> stk;
void tarjan(int u){
    instk[u]=true;
    stk.ep(u);
    dfsn[u]=low[u]=++tot;
    go(u,i){
        if(!dfsn[t])    tarjan(t),gmn(low[u],low[t]);
        else if(instk[t])   gmn(low[u],dfsn[t]);
    }
    if(dfsn[u]==low[u]){
        cscc++;
        int p=0;
        do{
            p=stk.top();stk.pop();
            scc[p]=cscc;
            instk[p]=false;
        }while(p^u);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y,a,b;scanf("%d%d%d%d",&x,&a,&y,&b);
        add(id(x,a),id(y,!b));add(id(y,b),id(x,!a));
    }
    for(int i=1;i<=n+n;i++)if(!dfsn[i])tarjan(i);
    for(int i=1;i<=n;i++)if(scc[i]==scc[i+n])exit(puts("IMPOSSIBLE")&0);
    puts("POSSIBLE");
    for(int i=1;i<=n;i++)   printf("%d ",scc[i]<scc[i+n]);
}