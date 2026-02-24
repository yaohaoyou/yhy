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
#define NO exit(puts("NO")&0)
using namespace std;
const int maxn=5e3+10;
int n,m;
int a[maxn];
namespace Graph{
    const int maxm=5e3+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
bool vis[maxn],inq[maxn];
ll dis[maxn];
int cur[maxn];
queue<int> q;
void spfa(int s){
    dis[s]=0;q.ep(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        inq[u]=false;vis[u]=true;
        go(u,i){
            if(dis[t]>dis[u]+w){
                dis[t]=dis[u]+w;
                if(!inq[t]){
                    if((++cur[t])>n)    NO;
                    q.ep(t),inq[t]=true;
                }
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(v,u,w);
    }
    mems(dis,0x3f);
    for(int i=1;i<=n;i++)if(!vis[i])spfa(i);
    for(int i=1;i<=n;i++)   printf("%lld ",dis[i]);puts("");
}