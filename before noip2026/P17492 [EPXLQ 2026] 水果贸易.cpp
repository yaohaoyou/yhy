#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pil pair<int,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=3e5+10,maxv=1e6+10;
const ll INF=1e12;
int n,m;
int a[maxn],b[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
// unordered_map<int,ll> f[maxn],g;
ll dp[maxn],ps[maxn],len[maxn];
multiset<pil,greater<pil>> f[maxn];
void dfs(int u,int ft){
    // for(int i=-s;i<=s;i++)f[u][i]=1ll*-i*(i<0?b[u]:a[u]);
    ps[u]=-INF;dp[u]=INF*b[u];
    f[u].ep(-b[u],INF);f[u].ep(-a[u],INF);
    len[u]=INF<<1;
    go(u,_)if(t^ft){
        dfs(t,u);
        while(ps[t]+f[t].begin()->se<-w) dp[t]+=f[t].begin()->fi*f[t].begin()->se,ps[t]+=f[t].begin()->se,len[t]-=f[t].begin()->se,f[t].erase(f[t].begin());
        assert(!f[t].empty());
        if(ps[t]<-w){
            auto [k,x]=*f[t].begin();f[t].erase(f[t].begin());
            dp[t]+=(-w-ps[t])*k;x-=(-w-ps[t]);len[t]-=(-w-ps[t]);ps[t]=-w;
            if(x)   f[t].ep(k,x);
        }
        while(ps[t]+len[t]-f[t].rbegin()->se>w)  len[t]-=f[t].rbegin()->se,f[t].erase(--f[t].end());
        if(ps[t]+len[t]>w){
            auto [k,x]=*f[t].rbegin();f[t].erase(--f[t].end());
            x-=(ps[t]+len[t]-w);len[t]=w-ps[t];
            // assert(x>=0);
            if(x)   f[t].ep(k,x);
        }
        assert(ps[t]==-w&&ps[t]+len[t]==w);
        dp[u]+=dp[t];ps[u]+=ps[t];len[u]+=len[t];
        if(f[u].size()<f[t].size()) f[u].swap(f[t]);
        for(auto i:f[t])    f[u].ep(i);
        f[t].clear();
        // g.swap(f[u]);f[u].clear();
        // for(auto [j,fj]:f[t])if(abs(j)<=w)for(auto [i,gi]:g)if(!f[u].count(i+j))f[u][i+j]=gi+fj;else gmx(f[u][i+j],gi+fj);
        // unordered_map<int,ll>().swap(f[t]);
    }
    // printf("%d %lld %lld : %lld\n",u,ps[u],len[u],dp[u]);
    // for(auto [i,j]:f[u])    printf("%d %lld\n",i,j);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(!~a[i])  a[i]=1e9;
    }
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)if(b[i]>a[i])return puts("-1"),0;
    for(int i=1;i<n;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);}
    dfs(1,0);
    while(ps[1]+f[1].begin()->se<-m) dp[1]+=f[1].begin()->fi*f[1].begin()->se,ps[1]+=f[1].begin()->se,f[1].erase(f[1].begin());
    assert(!f[1].empty());
    if(ps[1]<-m){
        auto [k,x]=*f[1].begin();f[1].erase(f[1].begin());
        dp[1]+=(-m-ps[1])*k;x-=(-m-ps[1]);ps[1]=-m;
    }
    assert(ps[1]==-m);
    printf("%lld\n",dp[1]);
}