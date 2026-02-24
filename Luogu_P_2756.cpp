#include<bits/stdc++.h>
using namespace std;
const int maxn=110,maxm=maxn*maxn*2,inf=0x3f3f3f3f;
int n,m;
namespace Graph{
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
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
int main(){
    scanf("%d%d",&m,&n);
    int u,v;
    while(~scanf("%d%d",&u,&v)&&u!=-1&&v!=-1){add(u,v,1);add(v,u,0);}
    T=n+1;
    for(int i=1;i<=m;i++){add(S,i,1);add(i,S,0);}
    for(int i=m+1;i<=n;i++){add(i,T,1);add(T,i,0);}
    printf("%d\n",dinic());
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=e[j].nxt){
            if(!e[j].w&&e[j].to&&e[j].to!=T&&i<e[j].to) printf("%d %d\n",i,e[j].to);
        }
    }
}