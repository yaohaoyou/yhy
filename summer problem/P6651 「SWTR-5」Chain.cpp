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
const int maxn=2e3+10,mod=1e9+7;
int n,m;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
const int maxm=4e4+10;
struct Graph{
    #define go(a,x,i) for(int i=a.head[x],t=a.e[i].to;i;i=a.e[i].nxt,t=a.e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}G,rG;
int sum;
int topu[maxn];
int dd[maxn],f[maxn],g[maxn],ff[maxn],dp[maxn][maxn];
int C[20][20];
queue<int> q;
void bfs1(){
    int tot=0;
    memc(dd,G.deg);
    for(int i=1;i<=n;i++)if(!G.deg[i])f[i]=1,q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();topu[u]=++tot;
        go(G,u,i){
            madd(f[t],f[u]);
            if(!(--dd[t])) q.ep(t);
        }
    }
    for(int i=1;i<=n;i++)if(!rG.deg[i]) madd(sum,f[i]);
}
void bfs2(){
    memc(dd,rG.deg);
    for(int i=1;i<=n;i++)if(!rG.deg[i])g[i]=1,q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        go(rG,u,i){
            madd(g[t],g[u]);
            if(!(--dd[t])) q.ep(t);
        }
    }
}
bool vis[maxn];
void dfs(int u){vis[u]=true;go(G,u,i)dd[t]++;go(G,u,i)if(!vis[t])dfs(t);}
void bfs3(int s){
    mems(vis,0);mems(dd,0);
    dfs(s);
    q.ep(s);dp[s][s]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        go(G,u,i){
            madd(dp[s][t],dp[s][u]);
            if(!(--dd[t]))    q.ep(t);
        }
    }
}
void init(){
    C[0][0]=1;
    for(int i=1;i<=15;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j],C[i-1][j-1]);
    }
}
int a[maxn];
int main(){
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);G.add(u,v);rG.add(v,u);}
    bfs1();bfs2();
    for(int i=1;i<=n;i++)   bfs3(i);
    int q;scanf("%d",&q);
    while(q--){
        int k;scanf("%d",&k);for(int i=1;i<=k;i++)scanf("%d",&a[i]);
        sort(a+1,a+k+1,[&](int x,int y){return topu[x]<topu[y];});
        for(int i=1;i<=k;i++)   ff[a[i]]=f[a[i]];
        int ans=sum;
        for(int i=1;i<=k;i++)
            for(int j=1;j<i;j++)
                mdel(ff[a[i]],immul(dp[a[j]][a[i]],ff[a[j]]));
        for(int i=1;i<=k;i++)   mdel(ans,immul(ff[a[i]],g[a[i]]));
        printf("%d\n",ans);
    }
}