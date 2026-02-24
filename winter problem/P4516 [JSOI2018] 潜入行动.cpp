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
const int maxn=1e5+10,maxk=110,mod=1e9+7;
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
int n,k;
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
int f[maxn][maxk][4],g[maxk][4],sum[maxn][maxk];  // f[u][i][0/1/2/3] 表示 u 子树内选了 i 个点，u 和 son 都没选/选了 son 没选 u/选了 u 的没选 son/u,son 都选 的方案数
int siz[maxn];
void dfs(int u,int ft){
    f[u][0][0]=f[u][1][2]=1;
    siz[u]=1;
    go(u,_){
        if(t==ft)   continue;
        dfs(t,u);
        memc(g,f[u]);mems(f[u],0);
        for(int i=0;i<=min(siz[u],k);i++){
            for(int j=0;j<=siz[t]&&i+j<=k;j++){
                madd(f[u][i+j][0],immul(g[i][0],f[t][j][1]));
                madd(f[u][i+j][1],imadd(immul(g[i][0],f[t][j][3]),immul(g[i][1],imadd(f[t][j][1],f[t][j][3]))));
                madd(f[u][i+j][2],immul(g[i][2],imadd(f[t][j][0],f[t][j][1])));
                madd(f[u][i+j][3],imadd(immul(g[i][2],imadd(f[t][j][2],f[t][j][3])),immul(g[i][3],sum[t][j])));
            }
        }
        siz[u]+=siz[t];
    }
    for(int i=0;i<=siz[u]&&i<=k;i++)    sum[u][i]=accumulate(f[u][i],f[u][i]+4,0ll)%mod;
    // for(int i=0;i<=siz[u]&&i<=k;i++)  printf("%d %d : %d %d %d\n",u,i,f[u][i][0],f[u][i][1],f[u][i][2]);
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    printf("%d\n",imadd(f[1][k][1],f[1][k][3]));
}