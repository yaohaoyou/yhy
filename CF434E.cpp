#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
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
const int maxn=1e5+10;
int n,mod,k,r;
int a[maxn],f[maxn],g[maxn],fa[maxn],dep[maxn],pq[maxn],mpq[maxn],in[maxn],out[maxn];
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
inline int qp(int x){return x>=0?pq[x]:mpq[-x];}
#define __div(x,s) all=s,findWC(x,0),divide(rt);
int all,rt;
int siz[maxn];bool bk[maxn];
void findWC(int u,int ft){
    siz[u]=1;int mx=0;
    go(u,i)if((t^ft)&&!bk[t]){
        findWC(t,u);
        siz[u]+=siz[t];
        gmx(mx,siz[t]);
    }
    gmx(mx,all-siz[u]);
    if(mx<=all/2)   rt=u;
}
__gnu_pbds::gp_hash_table<int,int> mp[2];
int L[maxn],R[maxn],rnk[maxn],tot;
void dfs(int u,int ft){
    L[u]=++tot;rnk[tot]=u;
    dep[u]=dep[fa[u]=ft]+1;siz[u]=1;
    f[u]=imadd(immul(f[ft],k),a[u]);g[u]=imadd(immul(a[u],pq[dep[u]]),g[ft]);
    go(u,i)if((t^ft)&&!bk[t])dfs(t,u),siz[u]+=siz[t];
    R[u]=tot;
}
void dfs2(int x){
    int l=fa[x];
    for(int i=L[x];i<=R[x];i++){
        int u=rnk[i],p=imdel(f[u],immul(f[l],qp(dep[u])));p=imdel(r,p);mmul(p,qp(-dep[u]));
        mp[0][p]++;
        mp[1][g[u]]++;
    }
}
void dfs3(int x){
    int l=fa[x];
    for(int i=L[x];i<=R[x];i++){
        int u=rnk[i],p=imdel(f[u],immul(f[l],qp(dep[u])));p=imdel(r,p);mmul(p,qp(-dep[u]));
        if(mp[0].find(g[u])!=mp[0].end())   in[u]+=mp[0][g[u]];
        if(mp[1].find(p)!=mp[1].end())   out[u]+=mp[1][p];
    }
}
void divide(int u){
    tot=0;bk[u]=true;dfs(u,0);
    vector<int> son;
    go(u,i)if(!bk[t])son.eb(t);
    {
        int p=r;mmul(p,qp(dep[u]));
        mp[0][p]++;mp[1][g[u]]++;
    }
    for(int t:son)  dfs3(t),dfs2(t);
    {
        int p=r;mmul(p,qp(dep[u]));
        if(mp[0].find(g[u])!=mp[0].end())   in[u]+=mp[0][g[u]];
        if(mp[1].find(p)!=mp[1].end())   out[u]+=mp[1][p];
    }
    mp[0].clear();mp[1].clear();
    reverse(son.begin(),son.end());
    for(int t:son)  dfs3(t),dfs2(t);
    mp[0].clear();mp[1].clear();
    go(u,i)if(!bk[t])__div(t,siz[t]);
}
int main(){
    scanf("%d%d%d%d",&n,&mod,&k,&r);pq[0]=1;
    for(int i=1;i<=n;i++)   pq[i]=immul(pq[i-1],k);
    for(int i=0;i<=n;i++)   mpq[i]=qpow(pq[i],mod-2);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dep[0]=-1;__div(1,n);
    ll ans=0;
    for(int i=1;i<=n;i++){
        ll x=n-in[i],y=n-out[i];
        ans+=y*n*3;
        ans-=x*x;
        ans-=y*y;
        ans-=x*y;
    }
    printf("%lld\n",1ll*n*n*n-ans);
}