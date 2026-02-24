//  P8435 【模板】点双连通分量
#include <bits/stdc++.h>
using namespace std;
const int maxn=6e5+10,maxm=2e6+10;
int n,m;
namespace Graph{
    int cnt;
    int head[maxn];
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
    int dfsn[maxn],low[maxn];
    stack<int> stk;
    int tot,bcc;
    vector<int> ans[maxn];
    void tarjan(int u,int fa){
        // printf("%d\n",u);
        low[u]=dfsn[u]=++tot;
        stk.push(u);
        int son=0;
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(!dfsn[t]){
                son++;
                tarjan(t,u);
                low[u]=min(low[u],low[t]);
                if(dfsn[u]<=low[t]){
                    bcc++;
                    int tp=-1;
                    do{
                        tp=stk.top();
                        ans[bcc].push_back(stk.top());
                        stk.pop();
                    }while(tp!=t);
                    ans[bcc].push_back(u);
                }
            }
            else low[u]=min(low[u],dfsn[t]);
        }
        if(fa==0&&son==0)   ans[++bcc].push_back(u);
    }
}
using namespace Tarjan;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        if(u==v)    continue;
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfsn[i]){
            tarjan(i,0);
        }
    }
    printf("%d\n",bcc);
    for(int i=1;i<=bcc;i++){
        printf("%d ",ans[i].size());
        for(auto j:ans[i])  printf("%d ",j);
        puts("");
    }
}