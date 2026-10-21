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
const int maxn=1e5+10,inf=1e9;
int n;
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
int fa[maxn],f[maxn],g[maxn],rk[maxn],ans[maxn];
vector<pii> v[maxn];
vector<int> pr[maxn],sf[maxn];
void dfs(int u){
    vector<int> tmp;
    go(u,i){
        dfs(t);
        v[u].eb(f[t],t);
        if(head[t]) tmp.eb(f[t]);
    }
    sort(tmp.begin(),tmp.end(),greater<int>());
    for(int i=0,c=1;i<tmp.size();i++,c+=2)gmx(ans[u],tmp[i]+c);
    sort(v[u].begin(),v[u].end(),greater<pii>());
    pr[u].resize(v[u].size());sf[u].resize(v[u].size());
    int c=1;
    for(int i=0,mx=0;i<v[u].size();i++,c+=2){
        rk[v[u][i].se]=i;
        gmx(mx,v[u][i].fi+c);
        pr[u][i]=mx;
    }
    c-=2;
    for(int i=int(v[u].size())-1,mx=0;~i;i--,c-=2){
        gmx(mx,v[u][i].fi+c);
        sf[u][i]=mx;
    }
    if(!v[u].empty())   gmx(f[u],pr[u].back());
    // printf("f[%d] = %d\n",u,f[u]);
}
void dfs2(int u){
    for(int i=0;i<v[u].size();i++){
        int t=v[u][i].se;
        g[t]=1+max({g[u],i?pr[u][i-1]:-inf,i+1<v[u].size()?(sf[u][i+1]-2):-inf});
        dfs2(t);
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=2;i<=n;i++)   scanf("%d",&fa[i]),add(fa[i],i);
    g[1]=-inf;
    dfs(1);dfs2(1);
    for(int i=1;i<=n;i++)   printf("%d ",max(ans[i],g[i]));
}