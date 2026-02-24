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
const int maxn=1e5+10,mod=1e9+7;
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
int n,m;
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
int tot;
int a[maxn],siz[maxn],son[maxn],dfsn[maxn],rnk[maxn];
int f[maxn],h[maxn];  // f[u] 表示 W[u]=0 时 u 子树内的方案数,h[u] 表示 u 子树内的方案数
// g[i][j] 表示从 dfsn[u] 到 i，和为 j 的方案数
void dfs(int u,int ft){
    siz[u]=1;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
        siz[u]+=siz[t];
        if(siz[t]>siz[son[u]])  son[u]=t;
    }
}
vector<int> ins(vector<int> f,int x){
    vector<int> g(m,0),s(m,0);
    // for(int i=1;i<=x;i++)for(int j=0;j<m;j++)madd(g[(i+j)%m],f[j]);
    if(!x)  return f;
    s[0]=f[0];
    for(int i=1;i<m;i++)    s[i]=imadd(s[i-1],f[i]);
    for(int i=0;i<m;i++){
        g[i]=immul(s[m-1],x/m);
        // for(int j=1;j<=x%m;j++)madd(g[i],f[(i-j+m)%m]);
        int y=(i-x%m+m)%m;
        if(x%m<=i)  madd(g[i],imdel(i?s[i-1]:0,y?s[y-1]:0));
        else    madd(g[i],i?s[i-1]:0),madd(g[i],imdel(s[m-1],y?s[y-1]:0));
        // debug("%d : g[%d] = %d\n",x,i,g[i]);
        // assert(g[i]>=0);
    }
    return g;
}
vector<int> dfs2(int u,int ft){
    vector<vector<int>> g(siz[u]-siz[son[u]],vector<int>(m,0));
    dfsn[u]=++tot;rnk[tot]=u;
    f[u]=1;
    if(son[u]){
        g[0]=dfs2(son[u],u);
        mmul(f[u],h[son[u]]);
        madd(g[0][0],f[son[u]]);
    }
    else{
        for(int i=0;i<m;i++)    g[0][i]=a[u]/m+(a[u]%m>=i);
        mdel(g[0][0],1);
        h[u]=imadd(f[u],g[0][0]);
        return g[0];
    }
    g[0]=ins(g[0],a[u]);
    int L=tot;
    go(u,_){
        if(t==ft||t==son[u])   continue;
        dfs2(t,u);
        mmul(f[u],h[t]);
        for(int i=dfsn[t];i<=dfsn[t]+siz[t]-1;i++){
            int x=rnk[i];
            for(int j=0;j<m;j++)madd(g[i+siz[x]-1-L][j],immul(g[i-1-L][j],f[x]));
            vector<int> tmp=ins(g[i-1-L],a[x]);
            for(int j=0;j<m;j++)madd(g[i-L][j],tmp[j]);
        }
    }
    h[u]=imadd(f[u],g[tot-L][0]);
    return g[tot-L];
}
int res[maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    dfs(1,0);dfs2(1,0);
    printf("%d\n",h[1]);
}