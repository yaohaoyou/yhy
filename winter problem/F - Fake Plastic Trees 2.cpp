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
const int maxn=1010,maxk=55;
int n,K;ll L,R;
ll a[maxn];
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
vector<ll> f[maxn][maxk],g[maxk];
void dfs(int u,int ft){
    f[u][0].eb(a[u]);
    go(u,_)if(t^ft){
        dfs(t,u);
        for(int i=0;i<=K;i++)   g[i].clear(),g[i].swap(f[u][i]);
        for(int i=0;i<=K;i++)for(ll k:g[i])for(int j=0;i+j<=K;j++){
            for(ll l:f[t][j]){
                if(k+l<=R)  f[u][i+j].eb(k+l);
                else break;
            }
        }
        for(int i=0;i<=K;i++){
            sort(f[u][i].begin(),f[u][i].end());
            f[u][i].erase(unique(f[u][i].begin(),f[u][i].end()),f[u][i].end());
            if(f[u][i].size()<=1) continue;
            vector<ll> tmp;tmp.clear();
            tmp.eb(f[u][i][0]);
            for(int j=1;j+1<f[u][i].size();j++)if(f[u][i][j+1]-tmp.back()>=R-L)tmp.eb(f[u][i][j]);
            tmp.eb(f[u][i].back());
            f[u][i].clear();f[u][i].swap(tmp);
        }
    }
    for(int i=0;i<=K;i++)
        for(ll j:f[u][i])if(j>=L&&(f[u][i+1].empty()||f[u][i+1][0]))f[u][i+1].insert(f[u][i+1].begin(),0);
}
void matt(int _cases){
    for(int i=1;i<=n;i++)for(int j=0;j<=K+1;j++)f[i][j].clear();
    for(int i=0;i<=K+1;i++) g[i].clear();
    rebuild();
    scanf("%d%d%lld%lld",&n,&K,&L,&R);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    if(*max_element(a+1,a+n+1)>R){
        for(int i=0;i<=K;i++)putchar('0');putchar('\n');
        return;
    }
    dfs(1,0);
    for(int i=0;i<=K;i++)printf("%d",(!f[1][i+1].empty()&&!f[1][i+1][0]));puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}