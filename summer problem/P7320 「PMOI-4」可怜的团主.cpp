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
const int maxn=1e3+10;
namespace Graph{
    const int maxm=maxn*maxn;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int n,m,fa[maxn],dep[maxn],deg[maxn];
bool vis[maxn];
vector<int> leaf;
void dfs(int u,int ft){
    // printf("%d %d\n",ft,u);
    vis[u]=true;
    dep[u]=dep[fa[u]=ft]+1;
    int son=0;
    go(u,i){
        int t=e[i].to;
        if(vis[t])   continue;
        deg[u]++;
        son++;
        dfs(t,u);
    }
    if(!son)  leaf.eb(u);
}
inline void print(int x,int y){
    vector<int> v1,v2;
    if(dep[x]<dep[y])   swap(x,y);
    while(dep[x]^dep[y])    v1.eb(x),x=fa[x];
    while(x^y)  v1.eb(x),v2.eb(y),x=fa[x],y=fa[y];
    reverse(v2.begin(),v2.end());
    printf("%d ",v1.size()+1+v2.size());
    for(int i:v1)   printf("%d ",i);
    printf("%d ",x);
    for(int i:v2)   printf("%d ",i);
    puts("");
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    if(leaf.size()>=n/3){
        puts("2");
        for(int i=0;i<n/3;i++)  printf("%d ",leaf[i]);
    }
    else{
        if(deg[1]==1)   leaf.eb(1);
        int k=(n+5)/6;
        puts("1");
        for(int i=0,j=leaf.size()/2;j<leaf.size();i++,j++)  k--,print(leaf[i],leaf[j]);
        for(int i=1;i<=k;i++)   print(i,i);
    }
}