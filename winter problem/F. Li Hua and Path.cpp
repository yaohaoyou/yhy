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
const int maxn=4e5+10;
int n;
const int maxm=maxn<<1;
struct Graph{
    #define go(o,x,i) for(int i=T[o].head[x],t=T[o].e[i].to;i;i=T[o].e[i].nxt,t=T[o].e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}T[3];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
}U;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){x--;for(;x<n;x|=x+1)tr[x]+=s;}
    inline int que(int x){int res=0;for(;x--;x&=x+1)res+=tr[x];return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}bit;
ll A,B,C;
int dfsn[maxn],d1[maxn],d2[maxn],sz1[maxn],sz2[maxn],tot;
void dfs1(int u){dfsn[u]=++tot;sz1[u]=1;go(1,u,i)d1[t]=d1[u]+1,dfs1(t),sz1[u]+=sz1[t];A+=sz1[u]-1;}
void dfs2(int u){sz2[u]=1;go(2,u,i)d2[t]=d2[u]+1,dfs2(t),sz2[u]+=sz2[t];B+=sz2[u]-1;}
void dfs3(int u){
    C+=bit.query(dfsn[u],dfsn[u]+sz1[u]-1);
    bit.add(dfsn[u],1);
    go(2,u,i)dfs3(t);
    bit.add(dfsn[u],-1);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);T[0].adde(u,v);}
    U.init();
    for(int u=n;u;u--){
        go(0,u,i){
            if(t<u) continue;
            t=U.find(t);
            T[1].add(u,t);
            U.merge(t,u);
        }
    }
    U.init();
    for(int u=1;u<=n;u++){
        go(0,u,i){
            if(t>u)    continue;
            t=U.find(t);
            T[2].add(u,t);
            U.merge(t,u);
        }
    }
    dfs1(1);dfs2(n);dfs3(n);
    printf("%lld\n",A+B-C-C);
    int q;scanf("%d",&q);
    for(int i=1;i<=q;i++){
        int x;scanf("%d",&x);
        d1[n+i]=d1[x]+1;A+=d1[n+i];
        B+=n+i-1;
        C+=d1[n+i];
        printf("%lld\n",A+B-C-C);
    }
}