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
const int maxn=1e5+10;
bool mem1;
int n,m;
namespace Graph{
    const int maxm=2e5+10;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
int p[maxn];
bool vis[maxn],ans[maxn];
vector<int> v[maxn];
bool in[maxn];
int up[maxn],L[maxn],R[maxn];
int tot;
bool mem2;
bool dfs(int u){
    L[u]=++tot;
    up[u]=0;in[u]=true;
    vis[u]=true;
    go(u,i){
        if(!vis[t]){
            if(!dfs(t))return false;
            up[u]+=up[t];
        }
        else if(!in[t])   return false;
        else    up[u]++,up[t]--,v[t].eb(L[u]);
    }
    in[u]=false;
    R[u]=tot;
    return true;
}
void dfs2(int u){
    // printf("u = %d,%d\n",u,up[u]);
    // for(int i:st)printf("%d ",i);puts("");
    if(up[u]==1&&ans[T.query(L[u],R[u])])   ans[u]=true;
    for(int i:v[u]) T.add(i,u);
    vis[u]=true;
    go(u,i){
        if(!vis[t])dfs2(t);
    }
    for(int i:v[u]) T.add(i,-u);
}
bool chk(int x){
    for(int i=1;i<=n;i++)v[i].clear();tot=0;
    fill(vis+1,vis+n+1,0);if(!dfs(x))return false;
    ans[x]=true;
    fill(vis+1,vis+n+1,0);dfs2(x);
    return true;
}
void matt(int _cases){
    rebuild();fill(ans+1,ans+n+1,0);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);add(u,v);}
    iota(p+1,p+n+1,1);random_shuffle(p+1,p+n+1);
    int T=min(n,100);
    while(T--){
        int x=p[T+1];
        if(chk(x))  break;
    }
    if(!~T) return puts("-1"),void();
    int cur=count(ans+1,ans+n+1,1);
    if(cur*5<n) return puts("-1"),void();
    for(int i=1;i<=n;i++)if(ans[i])printf("%d ",i);puts("");
}
int main(){srand(time(0));debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}