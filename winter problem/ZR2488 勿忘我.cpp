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
const int maxn=3e5+10;
int n,m;
namespace Graph{
    const int maxm=maxn<<2;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
int dfn[maxn];
namespace ST_LCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)
                st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using ST_LCA::LCA;
priority_queue<pii> q;
int tot;
int dep[maxn],fa[maxn],son[maxn];
bool ontr[maxm],vis[maxn];
void dfs(int u,int ft){
    dep[u]=dep[fa[u]=ft]+1;ST_LCA::st[0][dfn[u]=++tot]=ft;
    go(u,i){
        if(dep[t])   continue;
        ontr[i]=ontr[i^1]=true;
        son[u]++;
        dfs(t,u);
    }
}
inline int jump(int x,int d){while(d--)x=fa[x];return x;}
vector<int> a1,a2;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
int main(){
    // freopen("forget.in","r",stdin);freopen("forget.out","w",stdout);
    scanf("%d%d",&n,&m);
    if(n==1)    return puts("1"),0;
    U.init();
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);
        adde(u,v);
        u=U[u];v=U[v];
        if(u>v)swap(u,v);
        U.merge(u,v);
    }
    for(int i=2;i<=n;i++)if(U[i]==i)adde(1,i);
    dfs(1,0);ST_LCA::build();
    for(int i=1;i<=n;i++)if(!son[i])q.ep(dep[i],i);
    int lst=1;
    while(1){
        assert(!q.empty());
        int u=q.top().se;q.pop();if(u==1){a2.eb(u);break;}
        if(LCA(u,lst)==u){
            if(q.empty()){
                int x=0;
                while(u^1)a2.eb(x=u),u=fa[u];
                u=x;
                if(U[u]!=1){
                    reverse(a2.begin(),a2.end());
                    a1.insert(a1.begin(),1);
                    a1.swap(a2);
                }
                else a2.eb(1),reverse(a2.begin(),a2.end());
                break;
            }
            else{
                int v=q.top().se;q.pop();q.ep(dep[u],u);
                u=v;
            }
        }
        a1.eb(u);lst=u;
        if(!(--son[fa[u]])) q.ep(dep[fa[u]],fa[u]);
    }
    assert(a1.size()+a2.size()==n);
    for(int i:a2)   printf("%d ",i),vis[i]=true;
    for(int i:a1)   printf("%d ",i),vis[i]=true;
    puts("");
}