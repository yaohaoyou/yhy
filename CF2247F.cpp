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
bool mem1;
const int maxn=1e6+10,mod=998244353;
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
int n,m;
int pq[maxn],h[maxn];
vector<int> a[maxn],f[maxn],g[maxn];
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
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n*m+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
int siz[maxn],dep[maxn],fa[20][maxn];
inline int LCA(int x,int y){
    if(dep[x]<dep[y])   swap(x,y);
    if(x==y)return x;
    for(int i=19;~i;i--)if(dep[fa[i][x]]>=dep[y])x=fa[i][x];
    for(int i=19;~i;i--)if(fa[i][x]^fa[i][y])x=fa[i][x],y=fa[i][y];
    return fa[0][x];
}
inline int id(int x,int y){return (x-1)*m+y;}
void matt(int _cases){
    for(int i=1;i<=n;i++)a[i].clear(),f[i].clear(),g[i].clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        a[i].resize(m+1);f[i].resize(m+1);g[i].resize(m+1);
        for(int j=1;j<=m;j++)   scanf("%1d",&a[i][j]);
    }
    U.init();
    f[1][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if((i==1&&j==1)||(!a[i][j]))  continue;
            f[i][j]=imadd(i>1?f[i-1][j]:0,j>1?f[i][j-1]:0);
        }
    }
    g[n][m]=1;
    for(int i=n;i;i--){
        for(int j=m;j;j--){
            if((i==n&&j==m)||(!a[i][j]))  continue;
            g[i][j]=imadd(i<n?g[i+1][j]:0,j<m?g[i][j+1]:0);
        }
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)h[id(i,j)]=immul(f[i][j],g[i][j]);
    int cnt=0;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(!f[i][j]||!g[i][j])  cnt++;
    int ans=imdel(pq[cnt],1);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if((i!=1||j!=1)&&f[i][j]&&g[i][j]){
        bool c0=i>1&&f[i-1][j]&&g[i-1][j],c1=j>1&&f[i][j-1]&&g[i][j-1];
        int u=id(i,j);
        assert(c0||c1);
        if(c0&&c1)  fa[0][u]=LCA(id(i-1,j),id(i,j-1));
        else if(c0) fa[0][u]=id(i-1,j);
        else    fa[0][u]=id(i,j-1);
        if(h[u]==h[fa[0][u]])U.merge(u,fa[0][u]);
        dep[u]=dep[fa[0][u]]+1;
        for(int k=1;k<20;k++)fa[k][u]=fa[k-1][fa[k-1][u]];
    }
    for(int i=1;i<=n*m;i++)if(h[i])siz[U[i]]++;
    for(int i=1;i<=n*m;i++)if(siz[i])madd(ans,imdel(pq[siz[i]],1)),siz[i]=0;
    printf("%d\n",ans);
}
void init(){n=1e6;pq[0]=1;for(int i=1;i<=n;i++)pq[i]=imadd(pq[i-1],pq[i-1]);}
bool mem2;
int main(){debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);init();int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}