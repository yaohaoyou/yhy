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
const int maxn=1e5+10;
const int maxm=maxn<<1;
const ll INF=1e18;
bool mem1;
int n;
struct Graph{
    #define go(o,x,i) for(int i=T[o].head[x],t=T[o].e[i].to,w=T[o].e[i].w;i;i=T[o].e[i].nxt,t=T[o].e[i].to,w=T[o].e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}T[2];
bool vis[2][maxn];
int fa[maxn];ll dd[maxn],f[maxn],ans[maxn],dep[maxn];
int siz[maxn];
int rt,ALL;
int dfsn[maxn],tot;
int clr[maxn*18],cl;
vector<int> son;
namespace st_LCA{
    int Log[maxn],st[18][maxn];
    inline int mindfn(int x,int y){return dfsn[x]<dfsn[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)
                st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfsn[x])>(y=dfsn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline ll dis(int x,int y){return dd[x]+dd[y]-(dd[LCA(x,y)]<<1);}
}
using st_LCA::dis;
bool mem2;
void dfs1(int u,int ft){
    st_LCA::st[0][dfsn[u]=++tot]=ft;
    go(1,u,i){
        if(t==ft)   continue;
        dd[t]=dd[u]+w;
        dfs1(t,u);
    }
}
void findWC(int u,int ft,bool o){
    siz[u]=1;
    int mx=0;
    go(o,u,i){
        if(t==ft||vis[o][t])   continue;
        findWC(t,u,o);
        siz[u]+=siz[t];
        mx=max(mx,siz[t]);
    }
    mx=max(mx,ALL-siz[u]);
    if(mx*2<=ALL)    rt=u;
}
void divide2(int u){
    findWC(u,0,1);
    vis[1][u]=true;
    go(1,u,i){
        if(vis[1][t])  continue;
        ALL=siz[t];findWC(t,0,1);fa[rt]=u;divide2(rt);
    }
}
inline void ins(int u,ll a){int x=u;while(x){f[x]=min(f[x],a+dis(u,x));clr[++cl]=x;x=fa[x];}}
inline void query(int u,ll a){int x=u;while(x){ans[u]=min(ans[u],a+dis(u,x)+f[x]);x=fa[x];}}
void dfs2(int u,int ft){ins(u,dep[u]);go(0,u,i)if((t^ft)&&!vis[0][t])dfs2(t,u);}
void dfs3(int u,int ft){query(u,dep[u]);go(0,u,i)if((t^ft)&&!vis[0][t])dfs3(t,u);}
void dfs4(int u,int ft){siz[u]=1;go(0,u,i)if((t^ft)&&!vis[0][t]){dep[t]=dep[u]+w;dfs4(t,u);siz[u]+=siz[t];}}
inline void calc(int u){
    son.clear();
    go(0,u,i)if(!vis[0][t]) son.eb(t);
    dep[u]=0;dfs4(u,0);
    ins(u,dep[u]);
    for(int t:son){dfs3(t,u);dfs2(t,u);}
    for(int i=1;i<=cl;i++)f[clr[i]]=INF;cl=0;
    reverse(son.begin(),son.end());
    for(int t:son){dfs3(t,u);dfs2(t,u);}
    query(u,dep[u]);
    for(int i=1;i<=cl;i++)f[clr[i]]=INF;cl=0;
}
void divide1(int u){
    vis[0][u]=true;
    calc(u);
    go(0,u,i){
        if(vis[0][t])  continue;
        ALL=siz[t];findWC(t,0,0);divide1(rt);
    }
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    // freopen("D:\\yhy\\GDFZ_yhy\\down7.30\\frame\\frame2.in","r",stdin);
    freopen("frame.in","r",stdin);freopen("frame.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);T[0].adde(u,v,w);}
    for(int i=1;i<n;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);T[1].adde(u,v,w);}   
    mems(ans,0x3f);mems(f,0x3f);
    dfs1(1,0);st_LCA::build();
    ALL=n;findWC(1,0,1);divide2(rt);
    ALL=n;findWC(1,0,0);divide1(rt);
    for(int i=1;i<=n;i++)   printf("%lld\n",ans[i]);
}