//  P8436 【模板】边双连通分量
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=5e5+10,maxm=2e6+10;
int n,m;
namespace Graph{
    int cnt=1,head[maxn];
    struct edge{
        int nxt,to;
    }e[maxm<<1];
    void add(int u,int v){
        e[++cnt]={head[u],v};
        head[u]=cnt;
    }
}
using namespace Graph;
namespace Tarjan{
    int tot,dsccnt;
    vector<int> dscc[maxn];
    #define eb emplace_back
    int dfsn[maxn],low[maxn],scc[maxn];
    bool instk[maxn];
    stack<int> stk;
    void tarjan(int u,int fr){
        dfsn[u]=low[u]=++tot;
        instk[u]=true;
        stk.push(u);
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(!dfsn[t]){
                tarjan(t,i);
                low[u]=min(low[u],low[t]);
            }
            else if(i!=(fr^1))   low[u]=min(low[u],dfsn[t]);
        }
        if(dfsn[u]>low[u])  return;
        if(low[u]==dfsn[u]){
            ++dsccnt;
            int p=-1;
            while(p!=u){
                p=stk.top();
                stk.pop();
                instk[p]=false;
                scc[p]=dsccnt;
                dscc[dsccnt].eb(p);
            }
        }
    }
}
using namespace Tarjan;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    for(int i=1;i<=n;i++)
        if(!dfsn[i])    tarjan(i,maxm);
    printf("%d\n",dsccnt);
    for(int i=1;i<=dsccnt;i++){
        printf("%d ",dscc[i].size());
        for(int j:dscc[i])  printf("%d ",j);
        puts("");
    }
}