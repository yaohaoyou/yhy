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
inline void gmn(auto &x,auto y){__builtin_expect(x>y,0)&&(x=y);}
inline void gmx(auto &x,auto y){__builtin_expect(x<y,0)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=5010,mod=998244353;
struct mit{
    int v;
    mit(int _x=0){v=_x;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
int n;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
vector<int> son[maxn];
int tot,rt,all;
int fa[maxn],dep[maxn],rk[maxn],siz[maxn];
bool bk[maxn];
int k;
int up[maxn],buc[maxn];
int col[maxn],mxd[maxn],len[maxn];
mit ans,f[maxn],g[maxn],w[maxn],h[maxn][maxn];
void dfs2(int u,int ft){
    if(ft&&bk[ft])  col[u]=u;
    else    col[u]=col[ft];
    rk[++tot]=u;siz[u]=1;w[u]=1;
    mxd[u]=dep[u]=dep[ft]+1;
    len[u]=1;buc[dep[u]]=u;if(dep[u]>=k)up[u]=buc[dep[u]-k+1];
    go(u,i)if((t^ft)&&!bk[t])dfs2(t,u),gmx(len[u],max(len[t],mxd[u]-dep[u]+mxd[t]-dep[t]+1)),gmx(mxd[u],mxd[t]),siz[u]+=siz[t];
}
void findWC(int u,int ft){siz[u]=1;int mx=0;go(u,i)if((t^ft)&&!bk[t])findWC(t,u),siz[u]+=siz[t],gmx(mx,siz[t]);gmx(mx,all-siz[u]);if(mx*2<=all)rt=u;}
void dvd(int u){
    bk[u]=true;
    tot=0;dfs2(u,0);
    for(int i=tot;i;i--){
        int x=rk[i];f[x]=1;
        go(x,_)if(!bk[t]&&dep[t]==dep[x]+1)f[x]*=w[t];
        gmn(mxd[u],k);
        if(dep[x]<=k)g[dep[x]]+=f[x],h[col[x]][dep[x]]+=f[x];
        if(dep[x]>=k)   w[up[x]]+=f[x];
    }
    ans+=f[u]-1;g[1]=0;
    go(u,_)if(!bk[t]){
        for(int i=2;i<=mxd[t]&&i<=k/2+1;i++)ans+=h[t][i]*(g[k+2-i]-h[t][k+2-i]);
        for(int i=0;i<=mxd[t];i++)h[t][i]=0;
    }
    for(int i=0;i<=mxd[u];i++)g[i]=0;
    for(int t:son[u])if(len[col[t]]>=k)dvd(t);
}
void bld(int u){
    bk[u]=true;
    findWC(u,0);
    go(u,i)if(!bk[t]){
        all=siz[t];findWC(t,0);son[u].eb(rt);bld(rt);
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    int RT;
    all=n;findWC(1,0);RT=rt;bld(rt);
    for(k=1;k<=n;k+=2){
        mems(bk,0);
        dvd(RT);
        if(k==1)ans+=n;
    }
    printf("%d\n",ans);
}