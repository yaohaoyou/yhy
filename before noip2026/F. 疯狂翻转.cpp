#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2010;
bool mem1;
int n,m,k,tot;
int a[maxn][maxn],b[maxn][maxn],id[maxn][maxn];
pii c[maxn];
namespace Graph{
    const int maxm=maxn*4000;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn*maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=tot;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
vector<piii> ans;
bool vis[maxn*maxn];
void dfs(int u){
    vis[u]=true;
    int x=(u-1)/(m+1)+1,y=(u-1)%(m+1)+1;
    go(u,i)if(!vis[t]){
        dfs(t);
        int xx=(t-1)/(m+1)+1,yy=(t-1)%(m+1)+1;
        if(b[xx][yy]){
            // printf("(%d,%d) (%d,%d) %d\n",x,y,xx,yy,w);
            if(u==1)    ans.eb(pii(1,1),w);
            else if(x==xx)   ans.eb(pii(1,min(y,yy)),w);
            else    ans.eb(pii(min(x,xx),1),w);
            // b[x][y]^=1;b[xx][yy]^=1;
            xx=ans.back().fi.fi;yy=ans.back().fi.se;int p=c[w].fi,q=c[w].se;
            b[xx][yy]^=1;b[xx+p][yy]^=1;b[xx][yy+q]^=1;b[xx+p][yy+q]^=1;
        }
    }
}
bool mem2;
void matt(int _cases){
    rebuild();ans.clear();for(int i=0;i<=tot;i++)vis[i]=0;for(int i=0;i<=n+1;i++)for(int j=0;j<=m+1;j++)a[i][j]=0;
    scanf("%d%d%d",&n,&m,&k);
    tot=0;for(int i=1;i<=n+1;i++)for(int j=1;j<=m+1;j++)id[i][j]=++tot;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%1d",&a[i][j]);
    for(int i=1;i<=n+1;i++)for(int j=1;j<=m+1;j++)b[i][j]=a[i][j]^a[i-1][j]^a[i][j-1]^a[i-1][j-1];
    // for(int i=1;i<=n+1;i++,puts(""))for(int j=1;j<=m+1;j++)printf("%d",b[i][j]);
    for(int i=1;i<=k;i++){
        int x,y;scanf("%d%d",&x,&y);
        c[i]=pii(x,y);
        adde(id[1][1],id[1+x][1+y],i);
        for(int p=2;p+x<=n+1;p++)   adde(id[p][1+y],id[p+x][1+y],i);// (p,1) (p+x,1+y)
        for(int q=2;q+y<=m+1;q++)   adde(id[1+x][q],id[1+x][q+y],i);// (1,q) (1+x,q+y)
    }
    for(int i=1;i<=tot;i++)if(!vis[i]){
        int x=(i-1)/(m+1)+1,y=(i-1)%(m+1)+1;
        if((x==1)+(y==1)==1)    continue;
        dfs(i);
    }
    // printf("%d :\n",_cases);for(int i=1;i<=n+1;i++,puts(""))for(int j=1;j<=m+1;j++)printf("%d",b[i][j]);
    for(int i=1;i<=n+1;i++)for(int j=1;j<=m+1;j++)assert(!b[i][j]);
    printf("%d\n",ans.size());
    for(auto [t,i]:ans) printf("%d %d %d\n",i,t.fi,t.se);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}