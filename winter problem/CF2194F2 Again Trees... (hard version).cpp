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
const int maxn=1e5+10,maxK=(1<<10)+10,mod=1e9+7;
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
const int inv2=qpow(2,mod-2);
int n,k;
int a[maxn],b[maxn],f[maxn][maxK],g[maxK],sum[maxn];
// f[u][i] 表示 u 连通块的异或和 = sum[u]^ss[i] 的方案数
int ss[maxK];
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
inline void XORFWT(int *mp){
    const int m=(1<<k);
    for(int i=1;i<=k;i++)
        for(int j=0;j<m;j++)
            if(!(j&(1<<i-1))){
                int x=imadd(mp[j],mp[j^(1<<i-1)]),y=imdel(mp[j],mp[j^(1<<i-1)]);
                mp[j]=x;mp[j^(1<<i-1)]=y;
            }
}
inline void RXORFWT(int *mp){
    const int m=(1<<k);
    for(int i=1;i<=k;i++)
        for(int j=0;j<m;j++)
            if(!(j&(1<<i-1))){
                int x=imadd(mp[j],mp[j^(1<<i-1)]),y=imdel(mp[j],mp[j^(1<<i-1)]);
                mp[j]=immul(x,inv2);mp[j^(1<<i-1)]=immul(y,inv2);
            }
}
int fu[maxK],ft[maxK];
void dfs(int u,int fa){
    sum[u]=a[u];
    mems(f[u],0);
    f[u][0]=1;
    go(u,_)if(t^fa){
        dfs(t,u);
        memc(g,f[u]);mems(f[u],0);
        //! sum[u]^i sum[t]^j sum[u]^sum[t]^i^j
        memc(ft,f[t]);
        XORFWT(g);XORFWT(ft);
        for(int i=0;i<(1<<k);i++)   f[u][i]=immul(g[i],ft[i]);
        RXORFWT(f[u]);
        // for(int i=0;i<(1<<k);i++){
        //     for(int j=0;j<(1<<k);j++)madd(f[u][i^j],immul(g[i],f[t][j]));
        // }
        //! sum[u]^ss[i] sum[t]^ss[j]=b[k] sum[u]^ss[i]=sum[u]^sum[t]^ss[i]^sum[t]=(sum[u]^sum[t])^ss[i]^ss[j]^b[k]
        mems(ft,0);
        for(int K=1;K<=k;K++)
            for(int j=0;j<(1<<k);j++)   madd(ft[j^(1<<K-1)],(ss[j]==(sum[t]^b[K]))*f[t][j]);
        XORFWT(ft);
        for(int i=0;i<(1<<k);i++)   fu[i]=immul(g[i],ft[i]);
        RXORFWT(fu);
        for(int i=0;i<(1<<k);i++)   madd(f[u][i],fu[i]);
            // for(int i=0;i<(1<<k);i++){
                // for(int j:vs[sum[t]^b[K]])madd(f[u][i^j^(1<<K-1)],immul(g[i],f[t][j]));
                // for(int j=0;j<(1<<k);j++)if(ss[j]==(sum[t]^b[K]))madd(f[u][i^j^(1<<K-1)],immul(g[i],f[t][j]));
                // for(int j=0;j<(1<<k);j++)madd(f[u][i^j],immul(g[i],ft[j]));
            // }
        sum[u]^=sum[t];
    }
}
void matt(int _cases){
    rebuild();
    scanf("%d%d",&n,&k);
    for(int i=1,u,v;i<n;i++){scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=k;i++)   scanf("%d",&b[i]);
    for(int i=0;i<(1<<k);i++){ss[i]=0;for(int j=1;j<=k;j++)if(i&(1<<j-1))ss[i]^=b[j];}
    dfs(1,0);
    int ans=0;
    for(int i=0;i<(1<<k);i++){
        if(!f[1][i])    continue;
        // sum[1]^b[j]=ss[i];
        for(int j=1;j<=k;j++)if((sum[1]^ss[i])==b[j]){madd(ans,f[1][i]);break;}
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}