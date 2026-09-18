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
bool mem1;
const int maxn=3e4+10;
const ll B=3600000000;
int n,q;
int a[maxn];
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
int fa[20][maxn],dep[maxn];
ll w[maxn];
void dfs(int u,int ft){fa[0][u]=ft;dep[u]=dep[ft]+1;go(u,i)if(t^ft)dfs(t,u);}
int jp(int x,int d){for(int i=19;~i;i--)if(d&(1<<i))x=fa[i][x];return x;}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    dfs(1,0);
    for(int i=1;i<20;i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];
    for(int i=1;i<=n;i++)   w[i]=B*i+1ll*i*i;
    for(int i=1;i<=n;i++)   printf("%lld ",w[i]-w[fa[0][i]]);puts("");fflush(stdout);
    while(q--){
        ll x;scanf("%lld",&x);
        int d=x/B,p=(x%B)/d;
        int u=(d+p)/2,v=(p-d)/2;
        v=jp(u,dep[u]-dep[v]-1);
        printf("%d %d\n",u,v);fflush(stdout);
    }
}