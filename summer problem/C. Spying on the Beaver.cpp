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
const int maxn=1e5+10;
int n,m;
int a[maxn],f[maxn];
bool ans[maxn];
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
void dfs(int u,int ft){
    int s=a[u];
    go(u,i){
        dfs(t,u);
        a[u]+=a[t];
        if(a[t])    s++;
    }
    go(u,i)if(a[t]){
        s--;
        if(s)   ans[t]=true;
    }
}
void matt(int _cases){
    rebuild();
    fill(a+1,a+n+1,0);fill(ans+1,ans+n+1,0);
    scanf("%d",&n);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);add(x,i);}
    scanf("%d",&m);
    for(int i=1;i<=m;i++){int x;scanf("%d",&x);a[x]=1;}
    dfs(1,0);printf("%d ",count(ans+1,ans+n+1,1));
    for(int i=1;i<=n;i++)if(ans[i])printf("%d ",i);puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}