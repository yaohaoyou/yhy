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
const int maxn=5010,mod=1e9+7;
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
int fac[maxn],inv[maxn];
void init(){
    const int N=maxn-10;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int A(int x,int y){return x<y?0:immul(fac[x],inv[x-y]);}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
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
int siz[maxn],f[maxn],g[maxn];  // f[i] 表示钦定有 i 个点匹配到自己子树内的方案数
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
int main(){
    init();
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);dfs(rt,0);
    f[0]=1;
    go(rt,_){
        memc(g,f);
        for(int i=0;i<=n;i++)for(int j=1;j<=siz[t];j++)madd(f[i+j],immul(g[i],immul(C(siz[t],j),A(siz[t],j))));
    }
    // for(int i=0;i<n;i++)printf("%d ",f[i]);puts("");
    int ans=0;
    for(int i=0;i<n;i++){
        int w=immul(f[i],fac[n-i]);
        if(i&1) mdel(ans,w);
        else madd(ans,w);
    }
    printf("%d\n",ans);
}