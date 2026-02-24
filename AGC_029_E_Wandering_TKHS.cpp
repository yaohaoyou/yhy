#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e6+10;
int n;
int a[maxn];
namespace Graph{
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int ans;
int dep[maxn];
int c[maxn];
void dfs(int u,int fa,int mx,int se,int mxson){
    dep[u]=dep[fa]+1;
    if(u>mx)    se=mx,mx=u,mxson=0;
    else if(u>se)   se=u;
    if(u^1){
        if(dep[mx]>dep[se]) c[mx]++;
        else    c[mxson]++;
    }
    go(u,i){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs(t,u,mx,se,mxson?mxson:t);
    }
}
void dfs2(int u,int fa){
    go(u,i){
        if(e[i].to==fa) continue;
        c[e[i].to]+=c[u];
        dfs2(e[i].to,u);
    }
}
int main(){
    // freopen("maze.in","r",stdin);freopen("maze.out","w",stdout);
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        adde(u,v);
    }
    dfs(1,0,0,1,1);
    dfs2(1,0);
    for(int i=2;i<=n;i++)   printf("%d ",c[i]);
}