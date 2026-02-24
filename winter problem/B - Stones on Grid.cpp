#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10;
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
ll dis[maxn];
bool vis[maxn];
priority_queue<pli,vector<pli>,greater<pli>> q;
void dijkstra(int s){
    mems(dis,0x3f);
    q.ep(dis[s]=0,s);
    while(!q.empty()){
        int u=q.top().se;q.pop();if(vis[u])continue;
        vis[u]=true;
        go(u,i){
            if(dis[t]>dis[u]+w){
                dis[t]=dis[u]+w;
                if(!vis[t])q.ep(dis[t],t);
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    int S,T,W;
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        if(i==1)    S=u,T=v,W=w;
    }
    dijkstra(T);
    if(dis[S]^dis[0])   printf("%lld\n",dis[S]+W);
    else puts("-1");
}