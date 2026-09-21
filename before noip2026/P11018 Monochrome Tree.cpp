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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n;
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
int f[maxn][2][2],g[2][2];  // f[u][0/1][0/1] 表示 u 子树内都是 0/1，到根要异或 0/1 的最小操作次数
void dfs(int u,int ft){
    mems(f[u],0x3f);f[u][0][0]=f[u][1][0]=0;
    bool son=false;
    go(u,i)if(t^ft){
        dfs(t,u);son=true;
        memc(g,f[u]);
        f[u][0][0]=min(g[0][0]+f[t][0][0],g[0][1]+f[t][0][1]);
        f[u][0][1]=min(g[0][0]+f[t][0][1],g[0][1]+f[t][0][0]);
        f[u][1][0]=min(g[1][0]+f[t][1][0],g[1][1]+f[t][1][1]);
        f[u][1][1]=min(g[1][0]+f[t][1][1],g[1][1]+f[t][1][0]);
    }
    if(!son){
        f[u][a[u]][0]=0;
        f[u][!a[u]][1]=1;
        f[u][!a[u]][0]=1;
        f[u][a[u]][1]=2;
        return;
    }
    memc(g,f[u]);mems(f[u],0x3f);
    if(a[u]){
        f[u][0][1]=min(g[0][1],g[0][0]+1);
        f[u][1][0]=min(g[1][0],g[1][1]+1);
    }
    else{
        f[u][0][0]=min(g[0][0],g[0][1]+1);
        f[u][1][1]=min(g[1][1],g[1][0]+1);
    }
    memc(g,f[u]);
    gmn(f[u][0][0],g[1][0]+1);
    gmn(f[u][1][0],g[0][0]+1);
    gmn(f[u][0][1],g[1][1]+1);
    gmn(f[u][1][1],g[0][1]+1);
    // printf("%d : %d %d %d %d\n",u,f[u][0][0],f[u][0][1],f[u][1][0],f[u][1][1]);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    printf("%d\n",min(f[1][1][0],f[1][1][1]));
}