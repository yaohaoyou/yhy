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
const int maxn=3e3+10;
int n,m,ans;
const int maxm=maxn<<1;
struct Graph{
    #define go(o,x,i) for(int i=G[o].head[x],t=G[o].e[i].to;i;i=G[o].e[i].nxt,t=G[o].e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}G[2];
int p[maxn];
bool vis[maxn];
bitset<maxn> to[maxn],fr[maxn],bs;
vector<int> dom[maxn],son[maxn];
queue<int> q;
void bfs(int x,int o=0,int s=1){
    mems(vis,0);vis[x]=true;
    if(x==s)    return;
    q.ep(s);vis[s]=true;
    while(!q.empty()){
        int u=q.front();q.pop();
        go(o,u,i)if(!vis[t])q.ep(t),vis[t]=true;
    }
}
void dfs(int u){
    ans+=vis[u];
    for(int t:son[u])vis[t]|=vis[u],dfs(t);
}
int main(){
    int q;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);G[0].add(u,v);G[1].add(v,u);}
    for(int i=1;i<=n;i++){
        bfs(i);
        for(int j=1;j<=n;j++)if(!vis[j])dom[i].eb(j);
        for(int j=1;j<=n;j++)   to[j][i]=i==j?0:vis[j];
    }
    iota(p+1,p+n+1,1);sort(p+1,p+n+1,[&](int x,int y){return dom[x].size()<dom[y].size();});mems(vis,0);
    for(int i=1;i<=n;i++){
        int x=p[i];
        for(int j:dom[x])if(!vis[j]){
            son[x].eb(j);vis[j]=true;
            for(int k=1;k<=n;k++)   to[k][j]=to[k][x];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j:son[i]){
            bfs(i,1,j);
            for(int k=1;k<=n;k++)   fr[k][j]=i==k?0:vis[k];
        }
    }
    for(int _=1;_<=q;_++){
        int s,t;scanf("%d%d",&s,&t);
        ans=0;mems(vis,0);
        bs=to[s]&fr[t];
        for(int i=bs._Find_first();i<=n;i=bs._Find_next(i))vis[i]=true;
        dfs(1);
        printf("%d\n",ans);
    }
}