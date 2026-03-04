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
const int maxn=5e3+10,inf=1e9;
int n,m,S,T;
int d[maxn];
queue<int> q;
bool inq[maxn],vis[maxn];
namespace Graph{
    const int maxm=1e5+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w,co=e[i].co;i;i=e[i].nxt,t=e[i].to,w=e[i].w,co=e[i].co)
    #define gonow(x,i) for(int &i=now[x],t=e[i].to,w=e[i].w,co=e[i].co;i;i=e[i].nxt,t=e[i].to,w=e[i].w,co=e[i].co)
    int cnt=1;
    int head[maxn],now[maxn];
    struct edge{int nxt,to,w,co;}e[maxm];
    inline void add(int u,int v,int w,int co){e[++cnt]={head[u],v,w,co};head[u]=cnt;}
    inline void adde(int u,int v,int w,int co){add(u,v,w,co);add(v,u,0,-co);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
bool spfa(){
    queue<int>().swap(q);
    mems(d,0x3f);memc(now,head);mems(inq,0);
    d[S]=0;q.ep(S); 
    while(!q.empty()){
        int u=q.front();q.pop();inq[u]=false;
        go(u,i){
            if(!w||d[t]<=d[u]+co)  continue;
            d[t]=d[u]+co;
            if(!inq[t]) q.ep(t),inq[t]=true;
        }
    }
    return d[T]^d[0];
}
pii dfs(int u,int flw){
    if(u==T)    return pii(flw,0);
    vis[u]=true;
    int res=flw,c=0;
    gonow(u,i){
        if(!w||vis[t]||d[t]^(d[u]+co))   continue;
        // debug("%d %d\n",u,t);
        auto [fl,cost]=dfs(t,min(w,res));
        e[i].w-=fl;e[i^1].w+=fl;res-=fl;
        c+=cost+fl*co;
        if(!fl) d[t]=-1;
        if(!res)    break;
    }
    vis[u]=false;
    return pii(flw-res,c);
}
pii dinic(){
    int flow=0,cost=0;
    while(spfa()){pii t=dfs(S,inf);flow+=t.fi;cost+=t.se;}
    return pii(flow,cost);
}
int main(){
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1;i<=m;i++){
        int u,v,w,co;scanf("%d%d%d%d",&u,&v,&w,&co);
        adde(u,v,w,co);
    }
    pii t=dinic();
    printf("%d %d\n",t.fi,t.se);
}