#include<bits/stdc++.h>
#define NO return puts("No"),void()
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
const int maxn=1.2e5+10,maxp=(maxn<<4)+maxn;
int n,m,N;
pii a[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int fa[20][maxn];
int Log[maxn],dep[maxn],dfn[maxn],tot;
vector<int> son[maxp];int deg[maxp];
int tp[maxn],siz[maxn],Son[maxn],rnk[maxn];
namespace SegmentTree{
    #define ls (p<<1)
    #define rs (p<<1|1)
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int pos1[maxn],pos2[maxn];
    void bd(setpos){if(l==r)return pos1[l]=p,void();setmid;bd(lson);bd(rson);son[p].eb(ls);son[p].eb(rs);}
    void ad1(setpos,int pl,int pr,int x){if(l>=pl&&r<=pr)return son[x].eb(p),void();setmid;if(pl<=mid)ad1(lson,pl,pr,x);if(pr>mid)ad1(rson,pl,pr,x);}
    void bd2(setpos){if(l==r)return pos2[l]=p+N,void();setmid;bd2(lson);bd2(rson);son[ls+N].eb(p+N);son[rs+N].eb(p+N);}
    void ad2(setpos,int pl,int pr,int x){if(l>=pl&&r<=pr)return son[p+N].eb(x),void();setmid;if(pl<=mid)ad2(lson,pl,pr,x);if(pr>mid)ad2(rson,pl,pr,x);}
}
using namespace SegmentTree;
void add1(int x,int y,int z){
    while(tp[x]^tp[y]){
        if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
        ad1(all,dfn[tp[x]],dfn[x],z);
        x=fa[0][tp[x]];
    }
    if(dfn[x]>dfn[y])   swap(x,y);
    ad1(all,dfn[x],dfn[y],z);
}
void add2(int x,int y,int z){
    while(tp[x]^tp[y]){
        if(dep[tp[x]]<dep[tp[y]])   swap(x,y);
        ad2(all,dfn[tp[x]],dfn[x],z);
        x=fa[0][tp[x]];
    }
    if(dfn[x]>dfn[y])   swap(x,y);
    ad2(all,dfn[x],dfn[y],z);
}
namespace stLCA{
    int st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){dep[u]=dep[ft]+1;fa[0][u]=st[0][dfn[u]]=ft;go(u,i)if(t^ft)dfs(t,u);}
    void bd(){
        dfs(1,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
        for(int i=1;i<=Log[n];i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
inline int stp(int x,int d){for(int i=0;i<=Log[d];i++)if(d&(1<<i))x=fa[i][x];return x;}
void dfs1(int u,int ft){siz[u]=1;Son[u]=0;go(u,i)if(t^ft){dfs1(t,u);siz[u]+=siz[t];if(siz[t]>siz[Son[u]])Son[u]=t;}}
void dfs2(int u,int ft){
    rnk[dfn[u]=++tot]=u;
    if(Son[u])tp[Son[u]]=tp[u],dfs2(Son[u],u);
    go(u,i)if((t^ft)&&(t^Son[u]))tp[t]=t,dfs2(t,u);
}
void matt(int _cases){
    rebuild();tot=0;for(int i=0;i<=N+N+n+m;i++)deg[i]=0,son[i].clear();
    scanf("%d",&n);N=n<<2;
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs1(1,0);tp[1]=1;dfs2(1,0);
    stLCA::bd();
    scanf("%d",&m);
    for(int i=1;i<=m;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    bd(all);bd2(all);
    for(int i=1;i<=m;i++)   son[N+N+n+i].eb(pos2[dfn[a[i].fi]]),son[pos1[dfn[a[i].se]]].eb(N+N+n+i);
    for(int i=1;i<=m;i++){
        {
            auto [s,t]=a[i];
            int l=LCA(s,t);
            if(s==l)    s=stp(t,dep[t]-dep[s]-1);
            else    s=fa[0][s];
            add2(s,t,N+N+n+i);
        }
        {
            auto [s,t]=a[i];
            int l=LCA(s,t);
            if(t==l)    t=stp(s,dep[s]-dep[t]-1);
            else    t=fa[0][t];
            add1(s,t,N+N+n+i);
        }
    }
    for(int i=1;i<=N+N+n+m;i++)for(int j:son[i])deg[j]++;
    queue<int> q;int cur=0;
    for(int i=1;i<=N+N+n+m;i++)if(!deg[i])q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        cur++;
        for(int t:son[u])if(!(--deg[t]))q.ep(t);
    }
    puts(cur==N+N+n+m?"Yes":"No");
}
int main(){freopen("robot.in","r",stdin);freopen("robot.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}