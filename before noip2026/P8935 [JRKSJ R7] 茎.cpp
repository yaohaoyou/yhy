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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=510,mod=1e9+7;
struct mit{
    int v;
    mit(int x=0){v=x;}
    operator int()const{return v;}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
    inline mit& operator+=(int y){v+=y;(v>=mod)&&(v-=mod);return *this;}
    inline mit& operator-=(int y){v-=y;(v<0)&&(v+=mod);return *this;}
    inline mit& operator*=(int y){v=1ull*v*y%mod;return *this;}
};
inline mit qpow(mit x,int y){mit res=1;while(y){if(y&1)res*=x;x*=x;y>>=1;}return res;}
int n,k,x;
mit fac[maxn],inv[maxn];
inline mit C(int x,int y){return x<0||y<0||x<y?mit(0):fac[x]*inv[y]*inv[x-y];}
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
int siz[maxn],dep[maxn],fa[maxn],nx[maxn];
mit f[maxn][maxn],g[maxn][maxn],F[maxn];  // g[u][i] 表示 u 子树外选的节点个数为 i 的方案数（i 不包括 1 到 x 链上的点）
vector<int> path;
bool mk[maxn];
void dfs(int u,int ft){
    dep[u]=dep[fa[u]=ft]+1;
    siz[u]=1;mk[u]=(u==x);
    go(u,_)if(t^ft)dfs(t,u),mk[u]|=mk[t];
    if(mk[u])   path.eb(u);
    f[u][0]=1;
    int T=0;
    go(u,_)if((t^ft)&&!mk[t]){
        cpy(F,f[u],siz[u]);fll(f[u],0,siz[u]);
        for(int i=0;i<=siz[u];i++)for(int j=0;j<=siz[t];j++)f[u][i+j]+=F[i]*f[t][j]*C(i+j,i);
        siz[u]+=siz[t];
    }
    else if(t^ft)   T=t;
    if(T)   siz[u]+=siz[T],nx[u]=T;
    if(u==x){
        for(int i=k;i<=siz[u];i++)  f[u][i]=0;
    }
    else if(!mk[u]){
        for(int i=siz[u];i;i--)  f[u][i]+=f[u][i-1];
    }
}
void init(){
    n=500;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1);
}
bool mem2;
int main(){
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&k,&x);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    reverse(path.begin(),path.end());
    g[1][0]=1;
    ll sum=0;
    for(int u:path){
        if(u^1){
            for(int i=sum;~i;i--)   g[u][i]=g[u][i+1]+g[fa[u]][i];
        }
        if((u^x)&&(u^1)){
            for(int i=0;i<=sum;i++) g[u][i]+=g[fa[u]][i];
        }
        memc(F,g[u]);mems(g[u],0);
        for(int i=0;i<=sum;i++)for(int j=0;j<=siz[u]-siz[nx[u]];j++)g[u][i+j]+=F[i]*f[u][j]*C(i+j,i);
        sum+=siz[u]-siz[nx[u]];
    }
    printf("%d\n",g[x][k-1]);
}