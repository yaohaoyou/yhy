#include<bits/stdc++.h>
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=110,maxp=maxn,inf=0x3f3f3f3f;
int n,m;
namespace Graph{
    const int maxm=10100;
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,0);}
    void init(){for(int i=1;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int d[maxp],now[maxp];
int S,T;
queue<int> q;
inline bool bfs(){
    while(!q.empty())   q.pop();
    memset(d,0x3f,sizeof(d));
    memcpy(now,head,sizeof(head));
    d[S]=0;
    q.push(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(d[t]!=inf||e[i].w<=0)  continue;
            d[t]=d[u]+1;
            q.push(t);
            if(t==T)    return true;
        }
    }
    return false;
}
int dfs(int u,int flw){
    if(u==T)    return flw;
    int res=0;
    for(int i=now[u];i&&flw;i=e[i].nxt){
        now[u]=i;
        int t=e[i].to;
        if(d[t]!=d[u]+1||!e[i].w)    continue;
        int k=dfs(t,min(e[i].w,flw));
        if(!k)  d[t]=inf;
        e[i].w-=k;e[i^1].w+=k;
        res+=k;flw-=k;
    }
    return res;
}
int dinic(){
    int ans=0;
    while(bfs())    ans+=dfs(S,inf);
    return ans;
}
struct EDGE{int u,v,f;}E[maxm];int id[maxm];
bool fullflw[maxm];
int main(){
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1;i<=m;i++){
        int u,v,f;
        scanf("%d%d%d",&u,&v,&f);
        E[i]={u,v,f};
        if(f){adde(v,u,inf);adde(u,v,1);}
        else    adde(u,v,inf);
    }
    printf("%d\n",dinic());
    function<void(int)> dfs=[&](int u){
        fullflw[u]=true;
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(!e[i].w||fullflw[t])  continue;
            dfs(t);
        }
    };
    dfs(S);
    Graph::init();
    S=0;T=n+1;adde(S,T,inf);
    for(int i=1;i<=m;i++){
        if(E[i].f){
            adde(S,E[i].u,1);adde(E[i].u,E[i].v,inf);
            id[i]=cnt;adde(E[i].v,T,1);
        }
    }
    dinic();
    for(int i=1;i<=m;i++){
        if(!E[i].f) puts("0 547547547");
        else printf("%d %d\n",e[id[i]].w+547,fullflw[E[i].u]==fullflw[E[i].v]?547547547:e[id[i]].w+547);
    }
}