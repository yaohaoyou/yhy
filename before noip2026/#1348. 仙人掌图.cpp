#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10,lgV=29;
int n,m,q;
int pnt;
vector<piii> son[maxn];
int a[maxn];
int fa[maxn],fw[maxn],dep[maxn],X[maxn];
bool vis[maxn],in[maxn];
namespace Graph{
    const int maxm=2e6+10;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int dfn[maxn],tot;
bool ntr[maxn];
namespace stLCA{
    int st[21][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){st[0][dfn[u]=++tot]=ft;go(u,i)if(t^ft)dfs(t,u);}
    void build(){
        dfs(1,0);
        for(int i=1;i<=(31^__builtin_clz(tot));i++)for(int j=1;j+(1<<i)-1<=tot;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=31^__builtin_clz(y-x++);return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
struct Linear_basis{
    int p[lgV+1],t[lgV+1];
    Linear_basis(){mems(p,0);mems(t,0);}
    void ins(int x,int y){
        for(int i=lgV;~i;i--)if(x&(1<<i)){
            if(!p[i])   return p[i]=x,t[i]=y,void();
            if(y>t[i]){
                swap(p[i],x);
                swap(t[i],y);
            }
            x^=p[i];
        }
    }
    void mrg(Linear_basis &y,int lim=0){for(int i=lgV;~i;i--)if(y.p[i]&&y.t[i]>=lim)ins(y.p[i],y.t[i]);}
    inline int mn(int x,int lim){for(int i=lgV;~i;i--)if(t[i]>=lim)x=min(x,x^p[i]);return x;}
    void rebuild(int lim){
        for(int i=0;i<=lgV;i++)if(t[i]<lim)p[i]=0;
        for(int i=0;i<=lgV;i++)if(p[i])
            for(int j=0;j<i;j++)if(p[i]&(1<<j))p[i]^=p[j];
    }
    void print(){for(int i=0;i<=lgV;i++)printf("%d ",p[i]);puts("");}
    inline int kth(int x,int k){
        int r=count_if(p,p+lgV+1,[&](int x){return bool(x);});
        if(k>(1<<r))    return -1;
        for(int i=lgV;~i;i--)if(p[i]){
            if(k>(1<<r-1)){
                k-=(1<<r-1);
                if(!(x&(1<<i))) x^=p[i];
            }
            else if(x&(1<<i))   x^=p[i];
            r--;
        }
        return x;
    }
}lb[maxn];
void dfs(int u,int ft,int fr){
    X[u]=X[ft]^fw[u];
    in[u]=vis[u]=true;
    for(auto [t,w]:son[u])if(w.se^fr){
        if(!vis[t]) fa[t]=u,fw[t]=w.fi,dfs(t,u,w.se);
        else if(in[t]){
            int x=u,s=w.fi;pnt++;
            while(x^t){
                ntr[x]=true;
                adde(x,pnt);
                s^=fw[x],x=fa[x];
            }
            adde(t,pnt);a[pnt]=s;
        }
    }
    in[u]=false;
}
void dfs2(int u,int ft){
    dep[u]=dep[ft]+1;
    if(u>n) lb[u].ins(a[u],dep[u]);
    go(u,i)if(t^ft){
        lb[t]=lb[u];
        dfs2(t,u);
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);pnt=n;
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);son[u].eb(v,pii(w,i));son[v].eb(u,pii(w,i));}
    dfs(1,0,0);
    for(int i=2;i<=n;i++)if(!ntr[i])adde(fa[i],i);
    dfs2(1,0);
    stLCA::build();
    scanf("%d",&q);
    while(q--){
        int x,y,k;scanf("%d%d%d",&x,&y,&k);
        int s=X[x]^X[y];
        Linear_basis res;res.mrg(lb[x],dep[LCA(x,y)]);res.mrg(lb[y],dep[LCA(x,y)]);
        res.rebuild(dep[LCA(x,y)]);
        printf("%d\n",res.kth(s,k));
    }
}