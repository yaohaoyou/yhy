#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1010,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
ll x;
int n,m;
ll dep[maxn];int dd[maxn],fa[maxn];
namespace Graph{
    const int maxm=4e5+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
piii E[maxm];
bool flag[maxm];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
void dfs(int u,int ft){
    dd[u]=dd[fa[u]=ft]+1;
    go(u,i)if(t^ft){
        dep[t]=dep[u]+w;
        dfs(t,u);
    }
}
int main(){
    scanf("%d%d%lld",&n,&m,&x);
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);E[i]=piii(w,pii(u,v));}
    sort(E+1,E+m+1);
    U.init();
    ll W=0;
    for(int i=1;i<=m;i++){
        int w=E[i].fi,u=E[i].se.fi,v=E[i].se.se;
        if(U[u]!=U[v]){
            W+=w;
            U.merge(u,v);
            adde(u,v,w);
        }
        else    flag[i]=true;
    }
    if(W>x) return puts("0"),0;
    dfs(1,0);
    int B=W==x?n-1:0,C=0;
    for(int i=1;i<=m;i++)if(flag[i]){
        int w=E[i].fi,u=E[i].se.fi,v=E[i].se.se,mx=0;
        while(u^v){
            if(dd[u]<dd[v]) swap(u,v);
            gmx(mx,dep[u]-dep[fa[u]]);
            u=fa[u];
        }
        if(W-mx+w==x)   B++;
        else if(W-mx+w>x)  C++;
    }
    if(W==x)    printf("%d\n",imdel(qpow(2,B+C),qpow(2,C+1)));
    else printf("%d\n",imdel(qpow(2,B+C+1),qpow(2,C+1)));
}