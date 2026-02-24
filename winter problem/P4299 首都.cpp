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
const int maxn=1e5+10,maxq=3e5+10;
int n,m;
int a[maxn];
struct ques{int op,x,y;}Q[maxq];
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
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
int tot;
int siz[maxn],dep[maxn],dfsn[maxn],wc[maxn];
int fa[20][maxn],Log[maxn];
void dfs(int u,int ft){
    dfsn[u]=++tot;
    siz[u]=1;dep[u]=dep[fa[0][u]=ft]+1;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
        siz[u]+=siz[t];
    }
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=Log[dep[x]-dep[y]];~i;i--)if(dep[fa[i][x]]>=dep[y])x=fa[i][x];
    if(x==y)    return x;
    for(int i=Log[dep[x]];~i;i--)if(fa[i][x]^fa[i][y])x=fa[i][x],y=fa[i][y];
    return fa[0][x];
}
inline int S(int u){return T.query(dfsn[u],dfsn[u]+siz[u]-1);}
inline int jump(int u,int d){if(d<0)return u;for(int i=Log[d];~i;i--)if(d&(1<<i))u=fa[i][u];return u;}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
    U.init();
    for(int i=1;i<=m;i++){
        char s[5];scanf("%s",s);
        if(s[0]=='A')   Q[i].op=0,scanf("%d%d",&Q[i].x,&Q[i].y),U.merge(Q[i].x,Q[i].y),adde(Q[i].x,Q[i].y);
        if(s[0]=='Q')   Q[i].op=1,scanf("%d",&Q[i].x);
        if(s[0]=='X')   Q[i].op=2;
    }
    for(int i=1;i<=n;i++)if(U[i]!=U[1])U.merge(1,i),adde(1,i);
    dfs(1,0);for(int i=1;i<20;i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];
    U.init();
    int XOR=0;
    for(int i=1;i<=n;i++){
        XOR^=(wc[i]=i);
        T.add(dfsn[i],1);
        if(fa[0][i])    T.add(dfsn[fa[0][i]],-1);
    }
    for(int _=1;_<=m;_++){
        if(!Q[_].op){
            int x=Q[_].x,y=Q[_].y;
            if(dep[x]>dep[y])swap(x,y);
            int fx=U[x];assert(U[y]==y);
            int sy=S(y);T.add(dfsn[x],sy);if(fa[0][fx])T.add(dfsn[fa[0][fx]],-sy);
            U.merge(x,y);
            int wx=wc[fx],wy=wc[y],lca=LCA(wx,wy),all=S(fx),tx=jump(wx,dep[wx]-dep[lca]-1),ty=jump(wy,dep[wy]-dep[lca]-1);
            XOR^=wx;XOR^=wy;
            int u;
            if(wx==lca) u=wy;
            else if(wy==lca)    u=wx;
            else u=2*S(tx)>=all?wx:wy;
            for(int i=Log[dep[u]-dep[lca]];~i;i--){
                if(dep[fa[i][u]]<dep[lca]) continue;
                if(2*S(fa[i][u])<all)u=fa[i][u];
            }
            if(2*S(u)<all)  u=fa[0][u];
            wc[fx]=u;
            if(dep[fa[0][u]]>=dep[lca]&&2*S(u)==all) wc[fx]=min(wc[fx],fa[0][u]);
            XOR^=wc[fx];
        }
        else if(Q[_].op==1) printf("%d\n",wc[U[Q[_].x]]);
        else printf("%d\n",XOR);
    }
}