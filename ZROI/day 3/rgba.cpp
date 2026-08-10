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
const int maxn=1e5+10;
int n,m;
int be[maxn],en[maxn],l[maxn];
namespace Graph{
    const int maxm=1e6+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
}
using namespace Graph;
ll dis[maxn];
bool vis[maxn];
priority_queue<pli,vector<pli>,greater<pli>> pq;
void dijkstra(int s){
    mems(dis,0x3f);dis[s]=0;pq.ep(0,s);
    while(!pq.empty()){
        int u=pq.top().se;pq.pop();if(vis[u])continue;vis[u]=true;
        go(u,i){
            ll nw=dis[u]+w;
            if(nw%l[t]>en[t])   nw=(nw+l[t]-1)/l[t]*l[t];
            if(nw%l[t]<be[t])   nw+=be[t]-nw%l[t];
            if(dis[t]>nw){dis[t]=nw;pq.ep(dis[t],t);}
        }
    }
}
int main(){
    freopen("rgba.in","r",stdin);freopen("rgba.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=2;i<n;i++)    scanf("%d%d%d",&be[i],&en[i],&l[i]);
    l[n]=1;l[1]=1;
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    dijkstra(1);
    printf("%lld\n",dis[n]);
}