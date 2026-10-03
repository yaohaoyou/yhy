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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=100;
int n,m,a,b;
namespace Graph{
    const int maxm=210<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
int cur;
int siz[maxn],f[(1<<17)+10][maxn],id[maxn];
int ans[maxn];
bool vis[maxn];
priority_queue<pii,vector<pii>,greater<pii>> q;
void dijkstra(int s){
    mems(vis,0);
    for(int i=1;i<=n;i++)if(f[s][i]^f[0][0])q.ep(f[s][i],i);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=true;
        go(u,_){
            if(w==a){
                if(f[s][t]>(ll)f[s][u]+w){
                    f[s][t]=f[s][u]+w;
                    q.ep(f[s][t],t);
                }
            }
            else if(U[u]^U[t]){
                if(id[U[t]]==-1){
                    if(f[s][t]>(ll)f[s][u]+w){
                        f[s][t]=f[s][u]+w;
                        q.ep(f[s][t],t);
                    }
                }
                else if(!(s&(1<<id[U[t]]))) gmn(f[s|(1<<id[U[t]])][t],(ll)f[s][u]+w);
                // if(t==3)    printf("%d %d %d %d\n",s,u,id[U[t]],f[s][t]);
            }
        }
    }
}
int main(){
    scanf("%d%d%d%d",&n,&m,&a,&b);
    U.init();
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        adde(u,v,w);
        if(w==a)    U.merge(u,v);
    }
    for(int i=1;i<=n;i++)   siz[U[i]]++;
    mems(id,-1);
    for(int i=1;i<=n;i++)if(U[i]==i&&siz[i]>3)id[i]=cur++;
    // for(int i=1;i<=n;i++)   printf("%d,%d ",U[i],id[U[i]]);puts("");
    // printf("cur = %d\n",cur);
    mems(f,0x7f);mems(ans,0x7f);
    if(!~id[U[1]])    f[0][1]=0;
    else    f[1<<id[U[1]]][1]=0;
    // printf("%d\n",id[U[1]]);
    for(int i=0;i<(1<<cur);i++){
        dijkstra(i);
        for(int j=1;j<=n;j++)gmn(ans[j],f[i][j]);
    }
    for(int i=1;i<=n;i++)printf("%d ",ans[i]);puts("");
}