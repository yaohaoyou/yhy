#include<bits/stdc++.h>
using namespace std;
const int maxn=610,maxm=maxn<<2,inf=0x3f3f3f3f;
int n,m;
namespace Graph{
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,0);}
}
using namespace Graph;
int d[maxn],now[maxn];
int S,T;
queue<int> q;
inline bool bfs(){
    while(!q.empty())   q.pop();
    memset(d,0x3f,sizeof(d));
    memcpy(now,head,sizeof(head));
    d[0]=0;
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
int a[maxn],b[maxn];
int ans;
int main(){
    scanf("%d%d",&n,&m);
    T=n<<1|1;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    for(int i=1;i<=n;i++){
        ans+=abs(b[i]);
        adde(i,i+n,a[i]+abs(b[i]));
        if(b[i]<0)  adde(S,i,-2*b[i]);
        else    adde(i+n,T,2*b[i]);
    }
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);
        adde(u+n,v,inf);adde(v+n,u,inf);
    }
    ans-=dinic();
    printf("%d\n",ans);
}