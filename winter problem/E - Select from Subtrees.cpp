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
const int maxn=1e6+10,mod=998244353;
int n;
ll a[maxn];
int d[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
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
int fac[maxn],inv[maxn];
void init(){
    const int N=1e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
int C(ll x,int y){
    int res=1;
    for(int i=1;i<=y;i++)   mmul(res,(x-i+1)%mod);
    return immul(res,inv[y]);
}
int ans=1;
void dfs(int u){
    int x=0;
    go(u,i){
        dfs(t);
        a[u]+=a[t];
        x+=d[t];
    }
    if(x+d[u]>a[u]) exit(puts("0")&0);
    else    mmul(ans,C(a[u]-x,d[u]));
    d[u]+=x;
}
int main(){
    init();
    scanf("%d",&n);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);add(x,i);}
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&d[i]);
    dfs(1);
    printf("%d\n",ans);
}