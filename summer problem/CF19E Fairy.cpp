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
const int maxn=1e4+10;
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,rd;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v,0};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int sum;
int fa[maxn];
int c1[maxn],c2[maxn];
int dep[maxn];
bool vis[maxn];
vector<int> ans;
void dfs(int u,int ft){
    dep[u]=dep[fa[u]=ft]+1;
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        if(dep[t])  e[i].rd=1;
        if(u==t&&(i&1)) sum++;
        else if(dep[t]&&dep[t]<dep[u]){
            if((dep[u]-dep[t])&1)   c1[t]--,c1[u]++;
            else    c2[t]--,c2[u]++,sum++;
        }
        if(!dep[t]) dfs(t,u);
    }
}
void dfs2(int u){
    vis[u]=true;
    go(u,i){
        int t=e[i].to;
        if(vis[t])  continue;
        dfs2(t);
        c1[u]+=c1[t];c2[u]+=c2[t];
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++){
        if(dep[i])  continue;
        dfs(i,0);dfs2(i);
    }
    if(!sum){
        printf("%d\n",m);
        for(int i=1;i<=m;i++)   printf("%d ",i);puts("");
        exit(0);
    }
    for(int i=1;i<=m;i++){
        int u=e[i<<1].to,v=e[i<<1|1].to;
        if(dep[u]<dep[v])   swap(u,v);
        if(e[i<<1].rd){
            if(sum==1&&!((dep[u]-dep[v])&1))    ans.eb(i);
        }
        else if(c2[u]==sum&&!c1[u])  ans.eb(i);
    }
    printf("%d\n",ans.size());
    for(int i:ans)  printf("%d ",i);
}