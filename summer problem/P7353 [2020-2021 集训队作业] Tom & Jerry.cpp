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
const int maxn=2e5+10;
int n,m,q;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;debug("%d %d\n",u,v);}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
stack<int> stk;
vector<int> son[maxn];
int dfsn[maxn],low[maxn],cov[maxn],siz[maxn],tot;
void tarjan(int u){
    dfsn[u]=low[u]=++tot;
    stk.ep(u);
    for(int t:son[u]){
        if(!dfsn[t]){
            tarjan(t),gmn(low[u],low[t]);
            if(low[t]==dfsn[u]){
                m++;add(u,m);siz[m]=1;
                int tp=0;while(tp^t)siz[m]++,add(m,tp=stk.top()),stk.pop();
            }
        }
        else    gmn(low[u],dfsn[t]);
    }
}
int dep[maxn],fa[20][maxn];
int f[maxn],g[maxn];
void dfs(int u,int ft){dep[u]=dep[fa[0][u]=ft]+1;go(u,i)dfs(t,u);}
void dfs2(int u){go(u,i)dfs2(t),f[u]+=f[t]+(t>n&&cov[t]+1!=siz[t]);}
void dfs3(int u){
    int ft=fa[0][u];
    if(ft)  g[u]=g[ft]+f[ft]-f[u]+(ft>n&&cov[u]+1!=siz[ft]);
    go(u,i)dfs3(t);
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y])   swap(x,y);
    for(int i=19;~i;i--)if(dep[fa[i][x]]>=dep[y])x=fa[i][x];
    if(x==y)    return x;
    for(int i=19;~i;i--)if(fa[i][x]^fa[i][y])x=fa[i][x],y=fa[i][y];
    return fa[0][x];
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);son[u].eb(v);son[v].eb(u);}
    m=n;
    for(int i=1;i<=n;i++)if(!dfsn[i])tarjan(i);
    dfs(1,0);
    for(int i=1;i<20;i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];
    for(int u=1;u<=n;u++){
        for(int t:son[u])if(u<=t){
            if(dep[u]==dep[t])  cov[u]++,cov[t]++;
            else if(dep[u]>dep[t])  cov[u]++,cov[fa[0][u]]++;
            else    cov[t]++,cov[fa[0][t]]++;
        }
    }
    dfs2(1);dfs3(1);
    bool flag=false;
    for(int i=1;i<=n;i++)flag|=(!f[i]&&!g[i]);
    // for(int i=1;i<=m;i++)   printf("%d %d %d %d\n",f[i],g[i],cov[i],siz[i]);
    if(flag){debug("all yes\n");while(q--)puts("Yes");return 0;}
    while(q--){
        int a,b;scanf("%d%d",&a,&b);
        if(LCA(a,b)==a){
            for(int i=19;~i;i--)if(dep[fa[i][b]]>dep[a])b=fa[i][b];
            puts(f[b]+(cov[b]+1!=siz[b])?"No":"Yes");
        }
        else    puts(g[a]?"No":"Yes");
    }
}