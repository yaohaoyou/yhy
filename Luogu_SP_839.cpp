#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int maxn=510,M=3010,inf=0x3f3f3f3f;
int n,m;
int a[maxn];
pii g[M],p[maxn];
int S,T;
namespace Graph{
    const int maxm=maxn*maxn<<2;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void addedge(int u,int v,int w){add(u,v,w);add(v,u,0);}
    inline void initgraph(){cnt=1;memset(head,0,sizeof(head));}
}
using namespace Graph;
namespace DINIC{
    int d[maxn],now[maxn];
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
                if(d[t]!=inf||!e[i].w)  continue;
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
    inline void dinic(){
        while(bfs())    dfs(S,inf);
    }
}
int ans[maxn];
void Abstract(){
    memset(ans,0,sizeof(ans));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&g[i].first,&g[i].second);
    int k;
    scanf("%d",&k);
    for(int i=1;i<=k;i++)   scanf("%d%d",&p[i].first,&p[i].second);
    for(int s=0;s<31;s++){
        initgraph();
        S=0;T=n+1;  // 0 连 S,1 连 T
        for(int i=1;i<=k;i++){
            if(p[i].second&(1<<s))      addedge(S,p[i].first,inf);
            else    addedge(p[i].first,T,inf);
        }
        for(int i=1;i<=m;i++){add(g[i].first,g[i].second,1);add(g[i].second,g[i].first,1);}
        DINIC::dinic();
        for(int i=1;i<=n;i++)
            if(DINIC::d[i]!=inf)   ans[i]+=(1<<s);
    }
    for(int i=1;i<=n;i++)   printf("%d\n",ans[i]);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) Abstract();
}