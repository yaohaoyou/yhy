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
const int maxn=110<<1;
int n,m;
int a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];
namespace Graph{
    const int maxm=maxn*maxn;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
int p[maxn],q[maxn];
bool vis[maxn],used[maxn*maxn];
bool dfs(int u){
    go(u,i){
        int t=e[i].to;
        if(vis[t]||used[e[i].w])  continue;
        vis[t]=true;
        if(!p[t]||dfs(p[t]))    return p[t]=u,q[u]=e[i].w,true;
    }
    return false;
}
inline void print(auto arr){for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=m;j++)printf("%d ",arr[i][j]);}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){scanf("%d",&a[i][j]);adde(i,(a[i][j]-1)/m+1+n,a[i][j]);}
    for(int i=1;i<=m;i++){
        mems(p,0);
        for(int j=1;j<=n;j++){mems(vis,0);dfs(j);}
        for(int j=1;j<=n;j++)   b[j][i]=q[j],used[q[j]]=true;
    }
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)   c[(b[j][i]-1)/m+1][i]=b[j][i];
    print(b);print(c);
}