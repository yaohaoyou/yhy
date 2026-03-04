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
#define rng(arr) arr+1,arr+n+1
using namespace std;
const int maxn=2e5+10;
int n,m,k,l;
int a[maxn],b[maxn];
namespace Graph{
    vector<int> G[maxn],rG[maxn];
    int deg[maxn],dd[maxn];
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=dd[i]=deg[i]=0,G[i].clear(),rG[i].clear();cnt=1;}
}
using namespace Graph;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
priority_queue<pii,vector<pii>,greater<pii>> q;
queue<int> que;
bool vis[maxn];
int dis[maxn];
void dijkstra(){
    fill(vis+1,vis+n+1,0);
    fill(dis+1,dis+n+1,1e9);
    q.ep(dis[1]=0,1);
    while(!q.empty()){
        int u=q.top().se;q.pop();if(vis[u])continue;vis[u]=true;
        go(u,i){
            if(dis[t]>dis[u]+1) q.ep(dis[t]=dis[u]+1,t);
        }
    }
}
int pr[maxn],nx[maxn],id[maxn];
bool ans[maxn];
void bfs(){
    fill(pr+1,pr+n+1,0);fill(nx+1,nx+n+1,1e9);
    que.ep(1);
    while(!que.empty()){
        int u=que.front();que.pop();
        for(int t:G[u]){gmx(pr[t],pr[u]);if(id[u])gmx(pr[t],id[u]);if(!(--dd[t]))que.ep(t);}
    }
    for(int i=1;i<=n;i++)if(!deg[i])que.ep(i);
    while(!que.empty()){
        int u=que.front();que.pop();
        for(int t:rG[u]){gmn(nx[t],nx[u]);if(id[u])gmn(nx[t],id[u]);if(!(--deg[t]))que.ep(t);}
    }
}
void matt(int _cases){
    rebuild();fill(rng(id),0);fill(rng(ans),0);fill(rng(pr),0);fill(rng(id),0);
    scanf("%d%d%d%d",&n,&m,&k,&l);
    for(int i=1;i<=k;i++)   scanf("%d",&a[i]);
    if(find(a+1,a+k+1,1)==a+k+1)    a[++k]=1;
    for(int i=1;i<=l;i++)   scanf("%d",&b[i]);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dijkstra();
    sort(a+1,a+k+1,[&](int x,int y){return dis[x]<dis[y];});
    for(int i=1;i<=k;i++)   id[a[i]]=i;
    for(int u=1;u<=n;u++)go(u,i)if(dis[t]==dis[u]+1)G[u].eb(t),rG[t].eb(u),deg[u]++,dd[t]++;
    bfs();
    bool flag=false;
    for(int i=1;i<k;i++)if(nx[a[i]]!=i+1){flag=true;break;}
    for(int i=2;i<=k;i++)if(pr[a[i]]!=i-1){flag=true;break;}
    for(int i=1;i<=l;i++)if((a[k]==b[i]&&pr[b[i]]==k-1)||pr[b[i]]==k)que.ep(b[i]);
    if(flag||que.empty()){for(int i=2;i<=n;i++)putchar('0');puts("");return;}
    while(!que.empty()){
        int u=que.front();que.pop();ans[u]=true;
        for(int t:rG[u])if(pr[t]==k&&!ans[t])ans[t]=true,que.ep(t);
    }
    for(int i=2;i<=n;i++){
        if(ans[i])  continue;
        int p=lower_bound(a+1,a+k+1,i,[&](int x,int y){return dis[x]<dis[y];})-a;
        if(nx[i]==p&&pr[i]==p-1)    ans[i]=true;
        if(id[i])   ans[i]=true;
    }
    for(int i=2;i<=n;i++)   putchar(ans[i]+'0');puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}