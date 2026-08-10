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
const int maxn=3e5+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m,k;
vector<int> v[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    void rebuild(){cnt=1;for(int i=1;i<=n;i++)head[i]=0;}
}
using namespace Graph;
int fac[maxn],inv[maxn];
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void init(){int N=3e5;fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);}
int fa[maxn],b[maxn],c[maxn];
namespace st_LCA{
    int dfsn[maxn],tot;
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfsn[x]<dfsn[y]?x:y;}
    void dfs1(int u,int ft){
        st[0][dfsn[u]=++tot]=fa[u]=ft;
        go(u,i)if(t^ft)dfs1(t,u);
    }
    void build(){
        tot=0;dfs1(1,0);
        for(int i=2;i<=tot;i++) Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[tot];i++)
            for(int j=1;j+(1<<i)-1<=tot;j++)
                st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfsn[x])>(y=dfsn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using st_LCA::LCA;
void dfs(int u,int ft){go(u,i)if(t^ft){dfs(t,u);c[u]+=c[t];b[u]+=b[t];}}
void matt(){
    rebuild();for(int i=1;i<=n;i++)b[i]=c[i]=0;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    st_LCA::build();
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);
        int lca=LCA(u,v);
        b[u]++;b[v]++;b[lca]-=2;
        c[u]++;c[v]++;c[lca]--;c[fa[lca]]--;
    }
    dfs(1,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(c[i]>=k) madd(ans,C(c[i],k));
        if(b[i]>=k) mdel(ans,C(b[i],k));
    }
    printf("%d\n",ans);
}
int main(){init();int T;scanf("%d",&T);while(T--)matt();}