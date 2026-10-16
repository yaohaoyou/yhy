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
bool mem1;
const int maxn=6e5+10,mod=998244353;
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
int a[maxn],siz[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int fac[maxn],inv[maxn];
void init(){
    const int N=6e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y||x<0||y<0?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int f[maxn],g[maxn],h[maxn],fa[maxn],s[maxn],ss[maxn];
bool mem2;
void dfs(int u,int ft){
    fa[u]=ft;siz[u]=1;g[u]=f[u]=1;
    int all=1;
    go(u,i)if(t^ft){
        dfs(t,u);
        s[u]+=s[t];
        all+=siz[t];
        if(!~a[t])siz[u]+=siz[t];
        mmul(f[u],f[t]);
    }
    if(~a[u]){
        if(a[u]<s[u]){
            s[u]=a[u];a[u]=-2;
            // printf("u = %d %d\n",u,fa[u]);
        }
        else{
            swap(a[u],s[u]);a[u]=s[u]-a[u];
        }
        // if(a[u]<0)  a[u]=-2;
    }
    h[u]=f[u];
    if(~a[u])   mmul(f[u],C(siz[u],a[u]));
    mmul(g[fa[fa[u]]],f[u]);ss[fa[fa[u]]]+=s[u];
    if(~a[u])   mmul(g[u],C(all,s[u]-ss[u]));
    else    mmul(g[u],qpow(2,all));
}
void print(int u,int ft){printf("%d %d %d\n",u,ft,a[u]);go(u,i)if(t^ft)print(t,u);}
int main(){
    // freopen("five.in","r",stdin);freopen("five.out","w",stdout);
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    mems(a,-1);
    for(int i=1;i<=m;i++){int x,y;scanf("%d%d",&x,&y);a[x]=y;}
    dfs(1,0);
    int q;scanf("%d",&q);
    ll ans=0;
    for(int _=1;_<=q;_++){
        char s[5];int u,c;scanf("%s%d",s,&u);
        if(s[0]=='H')   ans^=1ll*_*g[u];
        else{
            scanf("%d",&c);
            int res=0;
            if(~a[u])   res=immul(h[u],imdel(C(siz[u]+c+1,a[u]+1),C(siz[u],a[u]+1)));
            else{
                res=immul(h[u],imdel(qpow(2,siz[u]+c+1),qpow(2,siz[u])));
            }
            mmul(res,qpow(c+1,mod-2));
            ans^=1ll*_*res;
            // printf("%d\n",res);
        }
    }
    printf("%lld\n",ans);
}