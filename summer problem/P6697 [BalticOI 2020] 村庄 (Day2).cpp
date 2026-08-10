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
int n;
int a[maxn],b[maxn];
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
int rt;
int dep[maxn],dfn[maxn],rnk[maxn],tot;
namespace stLCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){dep[u]=dep[ft]+1;st[0][dfn[u]=++tot]=ft;rnk[tot]=u;go(u,i)if(t^ft)dfs(t,u);}
    void build(){
        dfs(rt,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
int siz[maxn];
void dfs(int u,int ft){
    siz[u]=1;
    int mx=0;
    go(u,i)if(t^ft){
        dfs(t,u);
        mx=max(mx,siz[t]);siz[u]+=siz[t];
    }
    mx=max(mx,n-siz[u]);
    if(mx<=n/2)rt=u;
}
void dfs2(int u,int ft){
    go(u,i)if(t^ft)dfs2(t,u);
    if(b[u]==u){
        if(ft)  swap(b[u],b[ft]);
        else    go(u,i)if(t^ft){swap(b[u],b[t]);break;}
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    stLCA::build();
    for(int i=1;i<=n;i++)   a[rnk[i]]=rnk[(i+n/2-1)%n+1];
    iota(b+1,b+n+1,1);
    dfs2(1,0);
    ll ans=0;
    for(int i=1;i<=n;i++)   ans+=dis(b[i],i);
    printf("%lld ",ans);ans=0;
    for(int i=1;i<=n;i++)   ans+=dis(a[i],i);
    printf("%lld\n",ans);
    for(int i=1;i<=n;i++)   printf("%d ",b[i]);puts("");
    for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
}