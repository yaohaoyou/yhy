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
const int maxn=210,mod=1e9+7;
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
int n,rt,x;
int C[maxn][maxn];
int a[maxn],siz[maxn];
int f[maxn][maxn][2],g[maxn][maxn];  // f[u][i][0/1] 表示 u 子树内拓扑序第 i 个位置为 0/1 的方案数，g[u][i] 表示 u 子树内拓扑序第 i 个位置和第 i+1 个位置不同的方案数
int df[maxn][2],dg[maxn];
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
inline int mrg(int x,int y){return C[x+y][x];}
void dfs(int u,int ft){
    siz[u]=0;
    go(u,_)if(t^ft){
        dfs(t,u);
        if(!siz[u]){
            memc(f[u],f[t]);memc(g[u],g[t]);
            siz[u]=siz[t];
            continue;
        }
        memc(df,f[u]);mems(f[u],0);
        memc(dg,g[u]);mems(g[u],0);
        int au=imadd(df[1][0],df[1][1]),at=imadd(f[t][1][0],f[t][1][1]);
        for(int i=0;i<=siz[u];i++){
            for(int j=0;j<=siz[t];j++){
                if(i){
                    int w=1ull*at*mrg(i-1,j)%mod*mrg(siz[u]-i,siz[t]-j)%mod;
                    madd(f[u][i+j][0],immul(df[i][0],w));
                    madd(f[u][i+j][1],immul(df[i][1],w));
                }
                if(j){
                    int w=1ull*au*mrg(i,j-1)%mod*mrg(siz[u]-i,siz[t]-j)%mod;
                    madd(f[u][i+j][0],immul(f[t][j][0],w));
                    madd(f[u][i+j][1],immul(f[t][j][1],w));
                }
                if(i&&(i^siz[u]))   madd(g[u][i+j],1ull*at*mrg(i-1,j)%mod*dg[i]%mod*mrg(siz[u]-i-1,siz[t]-j)%mod);
                if(j&&(j^siz[t]))   madd(g[u][i+j],1ull*au*mrg(i,j-1)%mod*g[t][j]%mod*mrg(siz[u]-i,siz[t]-j-1)%mod);
                if(i&&j)    madd(g[u][i+j-1],2ull*mrg(i-1,j-1)*imadd(immul(df[i][0],f[t][j][1]),immul(df[i][1],f[t][j][0]))%mod*mrg(siz[u]-i,siz[t]-j)%mod);
            }
        }
        siz[u]+=siz[t];
    }
    siz[u]++;
    for(int i=siz[u];i;i--) swap(f[u][i][0],f[u][i-1][0]),swap(f[u][i][1],f[u][i-1][1]),swap(g[u][i],g[u][i-1]);
    f[u][1][u>x]=siz[u]==1?1:imadd(f[u][2][0],f[u][2][1]);g[u][1]=f[u][2][u<=x];
}
int main(){
    scanf("%d%d",&n,&rt);
    for(int i=0;i<=n;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}
    for(int i=1;i<n;i++){int x,y;scanf("%d%d",&x,&y);adde(x,y);}
    int ans=0;
    for(x=1;x<n;x++){
        mems(f,0);mems(g,0);
        dfs(rt,0);
        for(int i=1;i<n;i++)    madd(ans,g[rt][i]);
    }
    printf("%d\n",ans);
}