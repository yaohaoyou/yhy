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
const int maxn=400,inf=1e9;
bool mem1;
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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int f[maxn][maxn][maxn],g[maxn][maxn],siz[maxn];
bool mem2;
void dfs(int u,int ft){
    f[u][1][0]=f[u][0][1]=0;siz[u]=1;
    go(u,_)if(t^ft){
        dfs(t,u);
        for(int i=0;i<=max(siz[u],siz[t]);i++)for(int j=0;j<=siz[u]+siz[t];j++)g[i][j]=-inf;
        for(int i=0;i<=siz[u];i++)for(int j=0;j<=siz[u];j++)if(f[u][i][j]>=0)
            for(int p=0;p<=siz[t];p++)for(int q=0;q<=siz[t];q++)    gmx(g[max(i,p)][j+q],f[u][i][j]+f[t][p][q]);
        for(int i=0;i<=siz[u]+siz[t];i++)for(int j=0;j<=siz[u]+siz[t];j++)f[u][i][j]=-inf;
        for(int i=0;i<=max(siz[u],siz[t]);i++)for(int j=0;j<=siz[u]+siz[t];j++)if(g[i][j]>=0){
            for(int k=0;k<=j&&i+k<=siz[u]+siz[t];k++)gmx(f[u][i+k][j-k],g[i][j]);
        }
        siz[u]+=siz[t];
    }
    for(int i=0;i<=siz[u];i++)for(int j=0;j<=siz[u];j++)if(f[u][i][j]>=0)f[u][i][j]+=i;
}
void matt(int _cases){
    mems(f,-0x3f);mems(g,-0x3f);rebuild();
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    dfs(1,0);
    int ans=0;
    for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)gmx(ans,f[1][i][j]);
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}