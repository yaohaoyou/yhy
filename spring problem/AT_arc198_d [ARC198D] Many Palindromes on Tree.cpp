#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=3010;
int n;
int a[maxn][maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
struct DSU{
    int fa[maxn];
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void init(){for(int i=1;i<=n;i++)fa[i]=i;}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
}U;
vector<int> v[maxn];
int ans;
int nx[maxn][maxn],dep[maxn],lca[maxn][maxn];
bool vis[maxn][maxn],bk[maxn][maxn];
void dfs(int u,int ft){
    dep[u]=dep[ft]+1;
    v[u].eb(u);
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        dfs(t,u);
        for(int j:v[u])
            for(int k:v[t]) lca[j][k]=lca[k][j]=u;
        for(int j:v[t]) v[u].eb(j),nx[u][j]=t;
    }
    for(int i=1;i<=n;i++)   if(!nx[u][i])   nx[u][i]=ft;
}
int tot;
piii b[maxn*maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);U.init();
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%1d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            if(!a[i][j])    continue;
            int u=i,v=j;
            while(!vis[u][v]){
                vis[u][v]=vis[v][u]=true;U.merge(u,v);
                // printf("- %d %d %d %d\n",u,v,i,j);
                int x=nx[u][v],y=nx[v][u];u=x,v=y;
            }
        }
    for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)b[++tot]=piii(dep[i]+dep[j]-2*dep[lca[i][j]],pii(i,j));
    for(int i=1;i<=n;i++)   bk[i][i]=true;
    sort(b+1,b+tot+1);
    for(int i=1;i<=tot;i++){
        auto [u,v]=b[i].se;
        if(U.find(u)!=U.find(v))    continue;
        if(b[i].fi==1||bk[nx[u][v]][nx[v][u]]){
            ans++,bk[u][v]=bk[v][u]=true;
            // printf("%d %d\n",u,v);
        }
    }
    printf("%d\n",(ans<<1)+n);
}