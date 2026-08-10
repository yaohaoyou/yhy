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
const int maxn=4e5+10;
int n,m;
int a[maxn],rk[maxn],id[maxn];
queue<int> v[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
bool used[maxn];
unordered_map<int,int> mp[maxn];
int pos[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;mp[u][v]++;deg[u]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
vector<int> ans;
void dfs(int u){
    int x=v[u].front();v[u].pop();used[x]=true;
    if(deg[u]<=300){
        while(true){
            pii mn=pii(1e9,1e9);
            go(u,i)if(mp[u][t])mn=min(mn,pii(v[t].front(),t));
            if(mn.fi<=n){int t=mn.se;mp[u][t]--;mp[t][u]--;dfs(t);}
            else break;
        }
    }
    else{
        for(int i=pos[u]+1;i<=n;i=pos[u]+1){
            int t=id[i];
            if(!used[i]&&mp[u][t]){
                pos[u]=i;mp[u][t]--;mp[t][u]--;
                dfs(t);
            }
            else pos[u]=i;
        }
    }
    ans.eb(x);
}
void matt(int _cases){
    rebuild();for(int i=1;i<=n;i++)used[i]=rk[i]=pos[i]=0,mp[i].clear(),queue<int>().swap(v[i]);ans.clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    U.init();
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);
        U.merge(u,v);
    }
    for(int i=1;i<=n;i++)   id[i]=U[i];
    for(int i=1;i<=n;i++)   v[id[i]].ep(i);
    for(int i=1;i<n;i++)    adde(id[a[i]],id[a[i+1]]);
    dfs(id[a[1]]);
    reverse(ans.begin(),ans.end());for(int i:ans)printf("%d ",i);puts("");
    assert(ans.size()==n);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}