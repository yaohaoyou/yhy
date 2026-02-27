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
const int maxn=2e5+10,mod=998244353;
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
int n,op,ans;
int a[maxn],b[maxn],fac[maxn],inv[maxn],siz[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    vector<int> G[maxn];
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=deg[i]=0,G[i].clear();cnt=1;}
}
using namespace Graph;
void init(){
    const int N=2e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int pr[maxn],nx[maxn];queue<int> q;
inline void era(int x){pr[nx[x]]=pr[x];nx[pr[x]]=nx[x];}
void dfs(int u){siz[u]=1;for(int t:G[u])dfs(t),mmul(ans,inv[siz[t]]),siz[u]+=siz[t];mmul(ans,fac[siz[u]-1]);}
void matt(int _cases){
    rebuild();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),b[i]=a[i];
    for(int i=1;i<=n;i++)   pr[i]=i-1,nx[i]=i+1;pr[n+1]=n;
    {
        int tim=n,x=1;
        while(tim--){
            while(x<=n&&b[x])x=nx[x];
            if(x>n) return puts("0"),void();
            if(pr[x])   add(pr[x],x);
            if(nx[x]<=n)    add(nx[x],x);
            b[pr[x]]--;b[nx[x]]--;
            era(x);if(pr[x])x=pr[x];else x=nx[x];
        }
        if(x<=n)    return puts("0"),void();
        if(!op) return puts("1"),void();
    }
    ans=1;
    vector<int> rt;rt.clear();
    for(int i=1;i<=n;i++)if(!deg[i])q.ep(i),rt.eb(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        go(u,i)if(!(--deg[t])){G[u].eb(t);q.ep(t);}
    }
    for(int i:rt)   dfs(i);
    // for(int i=1;i<=n;i++)   printf("%d ",siz[i]);puts("");
    printf("%d\n",ans);
}
int main(){init();int T;scanf("%d%d",&T,&op);for(int i=1;i<=T;i++)matt(i);}