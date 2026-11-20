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
const int maxn=1e6+10;
int n,m;
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
int tot,cscc;
int dfsn[maxn],low[maxn],scc[maxn],out[maxn],in[maxn];
bool vis[maxn];
bool ins[maxn];
stack<int> stk;
vector<int> son[maxn];
void tarjan(int u){
    stk.ep(u);ins[u]=true;
    dfsn[u]=low[u]=++tot;
    go(u,i){
        if(!dfsn[t])    tarjan(t),gmn(low[u],low[t]);
        else if(ins[t]) gmn(low[u],dfsn[t]);
    }
    if(low[u]==dfsn[u]){
        cscc++;
        int p;
        do{
            p=stk.top();stk.pop();
            ins[p]=false;
            scc[p]=cscc;
        }while(p^u);
    }
}
bool mem2;
int main(){
    freopen("meowloop.in","r",stdin);freopen("meowloop.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);add(u,v);}
    for(int i=1;i<=n;i++)if(!dfsn[i])tarjan(i);
    if(cscc==1) return puts("0"),0;
    for(int u=1;u<=n;u++)go(u,i){
        if(scc[u]^scc[t]){
            son[scc[u]].eb(scc[t]),out[scc[u]]++;in[scc[t]]++;
        }
    }
    int ans1=0,ans2=0;
    for(int i=1;i<=cscc;i++)if(!in[i])ans1++;
    for(int i=1;i<=cscc;i++)if(!out[i])ans2++;
    printf("%d\n",max(ans1,ans2));
}