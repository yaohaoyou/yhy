#include<bits/stdc++.h>
#define ll long long
#define ull unsigned __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e6+10;
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    void rebuild(){cnt=1;for(int i=0;i<n;i++)head[i]=0;}
}
using namespace Graph;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
}U;
mt19937_64 Matt(time(0));
ull val[maxn],f[maxn];
bool vis[maxn];
unordered_map<int,int> mp[maxn];
void dfs1(int u,int fa){
    vis[u]=true;
    go(u,i){
        int t=e[i].to;
        if(t==fa)   continue;
        if(vis[t]&&!val[i>>1]){
            val[i>>1]=((ull)Matt()<<64)^Matt();
            f[u]^=val[i>>1];f[t]^=val[i>>1];
        }
        else if(!vis[t])    dfs1(t,u);
    }
}
void dfs2(int u,int fa){
    vis[u]=true;
    go(u,i){
        int t=e[i].to;
        if(t==fa||vis[t])   continue;
        dfs2(t,u);
        f[u]^=f[t];
        val[i>>1]=f[t];
    }
}
struct Linear_Basis{
    ull p[130];
    inline void clear(){mems(p,0);}
    inline bool ins(ull x){
        for(int i=127;~i;i--){
            if(!(x&(ull)(1)<<i))    continue;
            if(!p[i])   return p[i]=x;
            x^=p[i];
        }
        return false;
    }
}LB;
void matt(){
    rebuild();for(int i=0;i<n;i++)  mp[i].clear();
    int q;
    scanf("%d%d%d",&n,&m,&q);
    U.init();
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        val[i]=0;U.merge(u,v);
        if(mp[u].find(v)!=mp[u].end())  assert(0);
        if(mp[v].find(u)!=mp[v].end())  assert(0);
        adde(u,v);mp[u][v]=mp[v][u]=i;
    }
    for(int i=0;i<n;i++)   vis[i]=f[i]=0;
    dfs1(0,-1);for(int i=0;i<n;i++)vis[i]=0;dfs2(0,-1);
    LB.clear();
    bool flag=true;
    for(int i=0;i<n;i++)   flag&=U.find(i)==U.find(0);
    int x=0,y=0;
    while(q--){
        int u,v;scanf("%d%d",&u,&v);
        u=(u+x)%n;v=(v+y)%n;
        if(mp[u][v])    flag&=LB.ins(val[mp[u][v]]);
        mp[u][v]=mp[v][u]=false;
        puts(flag?"1":"0");
        x=(x*2+flag)%n;y=(y*3+flag)%n;
    }
}
int main(){int T;scanf("%d",&T);while(T--)matt();}