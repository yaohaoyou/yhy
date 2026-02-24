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
const int maxn=510;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w,co=e[i].co;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w,co;}e[maxm];
    inline void add(int u,int v,int w,int co){e[++cnt]={head[u],v,w,co};head[u]=cnt;}
    inline void adde(int u,int v,int w,int co){add(u,v,w,co);add(v,u,0,-co);}
    inline void rebuild(){for(int i=0;i<=tot;i++)head[i]=0;tot=0;cnt=1;}
}
using namespace Graph;
int n,m,k,tot;
int a[maxn][maxn],b[maxn][maxn],id[maxn][maxn];
void matt(int _cases){
    rebuild();
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<=n;i++)for(int j=0;j<=m;j++)id[i][j]=++tot;
    for(int i=1;i<=n;i++)for(int j=1;j<m;j++)scanf("%d",&a[i][j]),adde(id[i-1][j],id[i][j],a[i][j],0);
    for(int i=1;i<n;i++)for(int j=1;j<=m;j++)scanf("%d",&b[i][j]),adde(id[i][j-1],id[i][j],b[i][j],0);

}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}