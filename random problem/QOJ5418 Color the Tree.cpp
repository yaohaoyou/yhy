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
int n;
int a[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=1;i<=n;i++)head[i]=0;cnt=1;}
    vector<int> son[maxn];
}
using namespace Graph;
int Log[maxn];
int dfsn[maxn],tot;
struct STable{
    int st[20][maxn];
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=a[i];
        for(int i=1;i<20;i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    int query(int l,int r){l++;r++;int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
}st;
namespace lca{
    int st[20][maxn];
    int mindfn(int x,int y){return dfsn[x]<dfsn[y]?x:y;}
    void build(){
        for(int i=1;i<20;i++)
            for(int j=1;j<=n;j++)   st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfsn[x])>(y=dfsn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using lca::LCA;
int dep[maxn];
vector<int> v[maxn];
void dfs1(int u,int fa){
    v[dep[u]=dep[fa]+1].eb(u);
    lca::st[0][dfsn[u]=++tot]=fa;
    go(u,i){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs1(t,u);
    }
}
vector<int> init;
void build_virtual_tree(vector<int> vc){
    auto cmp=[&](int x,int y){return dfsn[x]<dfsn[y];};
    sort(vc.begin(),vc.end(),cmp);
    vector<int> tmp=vc;
    for(int i=1;i<vc.size();i++)    tmp.eb(LCA(vc[i-1],vc[i]));
    tmp.eb(1);
    sort(tmp.begin(),tmp.end(),cmp);tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
    init.clear();
    for(int i=1;i<tmp.size();i++){
        int u=tmp[i],v=LCA(tmp[i-1],tmp[i]);
        if(u^v) son[v].eb(u),init.eb(v);
    }
}
ll dp[maxn];
void dfs2(int u,int fa,int D){
    dp[u]=0;
    for(int t:son[u]){
        dfs2(t,u,D);
        dp[u]+=dp[t];
    }
    if(!dp[u])  dp[u]=st.query(D-dep[u],D-dep[fa]-1);
    else    dp[u]=min(dp[u],(ll)st.query(D-dep[u],D-dep[fa]-1));
}
void matt(){
    rebuild();tot=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs1(1,0);st.build();lca::build();
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(v[i].empty())    continue;
        build_virtual_tree(v[i]);v[i].clear();
        dfs2(1,0,i);
        for(int j:init) son[j].clear();
        ans+=dp[1];
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}