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
const int maxn=2e5+10;
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
int f[maxn],g[maxn];  // f[u] 表示 u 子树内的答案，g[u] 表示达成答案时的子树内颜色数
bool mem2;
void dfs(int u,int ft){
    int mx=0;
    go(u,i)if(t^ft){
        dfs(t,u);
        f[u]+=f[t];g[u]+=g[t];
        mx=max(mx,g[t]);
    }
    int w=min({m-1,g[u]/2,g[u]-mx});
    f[u]+=w;
    g[u]=min(m,g[u]-w+1);

}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    printf("%d\n",f[1]+n);
}