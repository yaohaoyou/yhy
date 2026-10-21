#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n;ll lim;
int leaf;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int lf[maxn],fa[maxn],fw[maxn];
ll up[maxn],dw[maxn],sdw[maxn],sup[maxn];
void dfs(int u,int ft){
    fa[u]=ft;
    dw[u]=0;
    lf[u]=(deg[u]==1);
    go(u,i)if(t^ft){
        fw[t]=w;
        dfs(t,u);
        lf[u]+=lf[t];
        gmx(dw[u],dw[t]+w);
        sdw[u]+=sdw[t]+1ll*lf[t]*w;
    }
}
void dfs2(int u,int ft){
    pll mx=pll(0,-1e9);
    go(u,i)if(t^ft){
        ll d=dw[t]+w;
        if(d>mx.fi) mx.se=mx.fi,mx.fi=d;
        else    gmx(mx.se,d);
    }
    go(u,i)if(t^ft){
        ll d=dw[t]+w;
        if(d==mx.fi)    up[t]=mx.se+w;
        else    up[t]=mx.fi+w;
        gmx(up[t],up[u]+w);
        sup[t]=(sdw[u]-sdw[t]-1ll*lf[t]*w)+sup[u]+1ll*(lf[1]-lf[t])*w;
        dfs2(t,u);
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%lld",&n,&lim);
    for(int i=1;i<n;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);}
    leaf=count(deg+1,deg+n+1,1);
    dfs(1,0);dfs2(1,0);
    // for(int i=1;i<=n;i++)   printf("%lld ",sup[i]);puts("");
    ll ans=1e18;
    for(int v=2;v<=n;v++){
        int l0=lf[v],l1=lf[1]-lf[v],w=fw[v];ll s0=sdw[v],s1=sup[v]-1ll*l1*w,mx0=dw[v],mx1=up[v]-w;
        if(l0>l1)   swap(l0,l1),swap(s0,s1),swap(mx0,mx1);
        ll l=0,r=1e18;
        while(l<=r){
            ll x=(l+r)>>1;
            double a=min(1.0*w,x/2.-mx0);
            if((x&1)&&(a==w))   a-=0.5;
            double b=w-a;
            // printf("%lld %.2f %.2f\n",x,a,b);
            if(a<0||b<0||x/2.-b<mx1){l=x+1;continue;}
            // printf("%lld %lld\n",x,(ll)(l0*(x/2.-a)+l1*(x/2.-b)-s0-s1));
            if(l0*(x/2.-a)+l1*(x/2.-b)-s0-s1>=lim)  gmn(ans,x),r=x-1;
            else    l=x+1;
        }
    }
    printf("%lld\n",ans);
}