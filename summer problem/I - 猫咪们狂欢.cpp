#include<bits/stdc++.h>
#define ep emplace
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1010,maxp=maxn*3,inf=1e9;
int n,k;
int a[maxn];
bool f[maxn];
namespace Graph{
    const int maxm=maxp<<3;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxp],now[maxp];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,0);}
    void rebuild(){cnt=1;mems(head,0);}
}
using namespace Graph;
int S,T;
int dep[maxp];
queue<int> q;
inline bool bfs(){
    while(!q.empty())q.pop();
    mems(dep,-1);memc(now,head);dep[S]=0;q.ep(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        go(u,i){
            if(!w||(~dep[t]))  continue;
            dep[t]=dep[u]+1;
            if(t==T)    return true;
            q.ep(t);
        }
    }
    return false;
}
int dfs(int u,int flow){
    if(u==T)    return flow;
    int res=flow;
    for(int i=now[u];i;i=e[i].nxt){
        now[u]=i;
        int t=e[i].to,w=e[i].w;
        if(dep[t]!=dep[u]+1||!w)    continue;
        int d=dfs(t,min(res,w));
        if(!d){dep[t]=-1;continue;} 
        res-=d;e[i].w-=d;e[i^1].w+=d;
        if(!res)    break;
    }
    if(res==flow)   dep[u]=-1;
    return flow-res;
}
int dinic(){int res=0;while(bfs())res+=dfs(S,inf);return res;}
void matt(){
    rebuild();mems(f,false);
    scanf("%d%d",&n,&k);
    S=0;T=n+1;
    for(int i=1;i<=k;i++)   scanf("%d",&a[i]),f[a[i]]=true,adde(S,a[i],0),adde(a[i],T,0);
    int tot=n+1,sum=0;
    for(int i=1;i<n;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        if(f[u]&&f[v])  adde(S,++tot,w),adde(tot,u,inf),adde(tot,v,inf),sum+=w;
    }
    for(int i=1;i<n;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        if(f[u]&&f[v])  adde(++tot,T,w),adde(u,tot,inf),adde(v,tot,inf),sum+=w;
    }
    printf("%d\n",sum-dinic());
}
int main(){int T;scanf("%d",&T);while(T--)matt();}