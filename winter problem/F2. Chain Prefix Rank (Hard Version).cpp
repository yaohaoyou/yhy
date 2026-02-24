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
const int maxn=5e5+10,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn];
unordered_set<int> son[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n+1;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
mt19937 Matt(time(0));
struct FHQTreap{
    int tot,rt;
    int siz[maxn],ls[maxn],rs[maxn],val[maxn],rnd[maxn];
    inline int nd(int x){int p=++tot;siz[p]=1;ls[p]=rs[p]=0;val[p]=x;rnd[p]=Matt();return p;}
    inline void pu(int p){siz[p]=siz[ls[p]]+siz[rs[p]]+1;}
    int merge(int p,int q){if(!p||!q)return p|q;if(rnd[p]<rnd[q])return rs[p]=merge(rs[p],q),pu(p),p;return ls[q]=merge(p,ls[q]),pu(q),q;}
    void split(int p,int v,int &x,int &y){
        if(!p)  return x=y=0,void();
        if(v<=siz[ls[p]])   split(ls[p],v,x,ls[y=p]);
        else split(rs[p],v-siz[ls[p]]-1,rs[x=p],y);
        pu(p);
    }
    inline int en(int p){while(rs[p])p=rs[p];return val[p];}
    inline int beg(int p){while(ls[p])p=ls[p];return val[p];}
    inline void clear(){rt=tot=0;}
}T;
int in[maxn],pr[maxn],nx[maxn];
int fac[maxn],inv[maxn];
queue<int> q;
unordered_map<int,int> f[maxn],g[maxn];  // f[u][v] 表示 u 到 v 的相对拓扑序方案数（不包括 u 和 v），g[u][v] 表示 u 到 v 的点数（不包括 u 和 v）
inline void add2(int u,int v){f[v][u]=1;g[v][u]=0;son[u].ep(v);in[v]++;}
void init(){
    const int N=5e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<0||y<0||x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
vector<int> path;
void dfs(int u){
    // auto it=path.begin();
    // for(int i=1;i<=a[u];i++)it++;
    // if(it!=path.end())  add2(*it,u),nx[u]=*it;
    // if(it!=path.begin())    add2(u,*prev(it)),pr[u]=*prev(it);
    // path.insert(it,u);
    int x,y;T.split(T.rt,a[u],x,y);
    if(x)   pr[u]=T.en(x),add2(u,pr[u]);
    if(y)   nx[u]=T.beg(y),add2(nx[u],u);
    T.rt=T.merge(x,T.merge(T.nd(u),y));
    go(u,i)dfs(t);
    x=y=0;
    T.split(T.rt,a[u],x,y);
    int z;
    T.split(y,1,y,z);
    T.rt=T.merge(x,z);
}
void bfs(){
    for(int i=0;i<=n+1;i++)if(in[i]==1&&son[i].size()==1)q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        if((in[u]^1)||(son[u].size()^1)) continue;
        int s=pr[u],t=nx[u];
        int fst=f[s][t],gst=g[s][t];
        f[s][t]=1ull*fst*f[s][u]%mod*f[u][t]%mod*C(gst+g[s][u]+g[u][t]+1,gst)%mod;
        g[s][t]=gst+g[s][u]+g[u][t]+1;
        son[t].erase(u);if(in[t]==1&&son[t].size()==1)q.ep(t);
        in[s]--;if(in[s]==1&&son[s].size()==1)q.ep(s);
        son[u].clear();
    }
}
void matt(int _cases){
    for(int i=0;i<=n+1;i++) son[i].clear(),f[i].clear(),g[i].clear(),in[i]=pr[i]=nx[i]=0;
    path.clear();T.clear();
    rebuild();
    scanf("%d",&n);
    for(int i=2;i<=n;i++){int x=0;scanf("%d",&x);add(x,i);}
    a[0]=0;a[n+1]=1;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),a[i]++;
    add(0,n+1);add(n+1,1);
    dfs(0);
    bfs();
    printf("%d\n",f[0][n+1]);
}
int main(){init();int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}