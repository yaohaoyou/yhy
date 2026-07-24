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
const int maxn=3e5+10;
int n,m,a[maxn];
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
void dfs(int u,int ft){a[u]=a[ft]+1;go(u,i)if(!a[t]&&(t^1))dfs(t,u);}
void matt(int _cases){
	rebuild();
    scanf("%d%d",&n,&m);fill(a+1,a+n+1,0); 
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    a[0]=-1;dfs(1,0);
    for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
