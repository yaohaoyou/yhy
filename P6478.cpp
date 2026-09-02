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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=5010,mod=998244353;
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
int siz[maxn][2];
int f[maxn][maxn],tmp[maxn],fac[maxn];
int F[maxn],G[maxn],C[maxn][maxn];
void dfs(int u,int ft){
    f[u][0]=1;
    go(u,_)if(t^ft){
        dfs(t,u);
        memc(tmp,f[u]);mems(f[u],0);
        int su=min(siz[u][0],siz[u][1]),sv=min(siz[t][0],siz[t][1]);
        for(int i=0;i<=su;i++)for(int j=0;j<=sv;j++)if(tmp[i]&&f[t][j])madd(f[u][i+j],immul(tmp[i],f[t][j]));
        siz[u][0]+=siz[t][0];
        siz[u][1]+=siz[t][1];
    }
    int su=min(siz[u][0],siz[u][1]);
    for(int i=su;~i;i--){
        if(!f[u][i]||i==siz[u][!a[u]])    continue;
        madd(f[u][i+1],immul(f[u][i],siz[u][!a[u]]-i));
    }
    siz[u][a[u]]++;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=immul(fac[i-1],i);
    for(int i=0;i<=n;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j],C[i-1][j-1]);}
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    for(int i=0;i<=n>>1;i++)    F[i]=immul(f[1][i],fac[(n>>1)-i]);
    for(int i=0;i<=n>>1;i++){
        for(int j=i;j<=n>>1;j++)
            if((j-i)&1)mdel(G[i],immul(C[j][i],F[j]));
            else    madd(G[i],immul(C[j][i],F[j]));
        printf("%d\n",G[i]);
    }
}