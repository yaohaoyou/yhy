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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=210,inf=1e9;
int n,m,S,T;
int d[maxn];
queue<int> q;
namespace Graph{
    const int maxm=1e4+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    #define gonow(x,i) for(int &i=now[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn],now[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,0);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
bool bfs(){
    queue<int>().swap(q);
    mems(d,-1);memc(now,head);
    d[S]=0;q.ep(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        go(u,i){
            if(~d[t]||!w)  continue;
            d[t]=d[u]+1;
            if(t==T)    return true;
            q.ep(t);
        }
    }
    return false;
}
int dfs(int u,int flw){
    if(u==T)    return flw;
    int res=flw;
    gonow(u,i){
        if(!w||d[t]^(d[u]+1))   continue;
        int fl=dfs(t,min(w,res));
        e[i].w-=fl;e[i^1].w+=fl;res-=fl;
        if(!fl) d[t]=-1;
        if(!res)    break;
    }
    return flw-res;
}
ll dinic(){
    ll flow=0;
    while(bfs())    flow+=dfs(S,inf);
    return flow;
}
int main(){
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        adde(u,v,w);
    }
    printf("%lld\n",dinic());
}