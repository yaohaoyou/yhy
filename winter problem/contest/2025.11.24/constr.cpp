#include<bits/stdc++.h>
#define ppc(x) __builtin_popcount(x)
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
const int maxn=20,maxN=(1<<16)+10;
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
int ans[maxn];
void dfs(int u,int ft){go(u,i)if(t^ft){ans[t]=ans[u]^w;dfs(t,u);}}
int main(){
    freopen("constr.in","r",stdin);freopen("constr.out","w",stdout);
    scanf("%d",&n);m=(1<<n)-1;
    printf("%d\n",1<<n-1);
    for(int i=1;i<=n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v,1<<(i-1));}
    for(int i=0;i<=m;i++){
        if(ppc(i)&1)    continue;
        ans[0]=i;dfs(0,0);
        for(int j=0;j<=n;j++)   printf("%d ",ans[j]);puts("");
    }
}