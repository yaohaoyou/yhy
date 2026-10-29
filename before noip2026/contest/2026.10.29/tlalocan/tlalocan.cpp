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
bool mem1;
const int maxn=20,maxm=maxn*maxn,maxN=(1<<18)+10,mod=998244353;
int n,m;
int G[maxn];
pii a[maxm];
namespace Graph{
    const int maxe=maxm<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxe];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=deg[i]=0;cnt=1;}
}
using namespace Graph;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
mit pq[maxn];
inline int lb(int x){return x&-x;}
mit f[maxN];
int g[maxN],c[maxN];
bool mem2;
int main(){
    freopen("tlalocan.in","r",stdin);freopen("tlalocan.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);const int N=(1<<n)-1;
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=pq[i-1]*2;
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);a[i]=pii(u,v);
        G[u]|=1<<v-1;G[v]|=1<<u-1;
    }
    for(int i=1;i<=N;i++){
        int x=__lg(lb(i))+1;
        g[i]=g[i^lb(i)]+__builtin_popcount(G[x]&i);
        U.init();
        for(int j=1;j<=n;j++)if(i&(1<<j-1))for(int k=1;k<=n;k++)if((G[j]&i)&(1<<k-1))U.merge(j,k);
        for(int j=1;j<=n;j++)if((i&(1<<j-1))&&(U[j]==j))c[i]++;
    }
    f[0]=1;
    for(int s=0;s<=N;s++){
        for(int t=s;t;t=(t-1)&s){
            if(c[t]&1)  f[s]+=f[s^t];
            else    f[s]-=f[s^t];
        }
    }
    printf("%d\n",f[N]);
}