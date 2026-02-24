#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,q;
int a[maxn];
namespace Graph{
    int cnt;
    int head[maxn];
    struct edge{int nxt,to;}e[maxn<<1];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
}
using namespace Graph;
int dfsn[maxn],R[maxn];int tot;
void dfs(int u,int fa){
    dfsn[u]=++tot;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs(t,u);
    }
    R[u]=tot;
}
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1,0);
    while(q--){
        int r,x;
    }
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) solve();
}