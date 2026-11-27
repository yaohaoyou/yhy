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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e6+10;
int n,m;
inline int id(int x,int o){return x+o*n;}
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int tot;
stack<int> stk;
bool ins[maxn];
int cscc;
int dfn[maxn],low[maxn],scc[maxn];
void tarjan(int u){
    stk.ep(u);ins[u]=true;
    dfn[u]=low[u]=++tot;
    go(u,i){
        if(!dfn[t])    tarjan(t),gmn(low[u],low[t]);
        else if(ins[t]) gmn(low[u],dfn[t]);
    }
    if(low[u]==dfn[u]){
        int p;cscc++;
        do{
            p=stk.top();stk.pop();
            ins[p]=false;scc[p]=cscc;
        }while(p^u);
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,a,y,b;scanf("%d%d%d%d",&x,&a,&y,&b);
        add(id(x,!a),id(y,b));
        add(id(y,!b),id(x,a));
    }
    for(int i=1;i<=n+n;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++)if(scc[i]==scc[i+n])return puts("IMPOSSIBLE"),0;
    puts("POSSIBLE");
    // 拓扑序大的是正确的，scc 小的是正确的
    for(int i=1;i<=n;i++)printf("%d ",scc[i]>scc[i+n]);
}