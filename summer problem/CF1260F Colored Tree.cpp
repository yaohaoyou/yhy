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
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
int n;
int ans,ALL=1;
int a[maxn],l[maxn],r[maxn];
vector<int> ins[maxn<<1],del[maxn<<1];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int all,rt;
int siz[maxn],dep[maxn],bel[maxn];
int vl[maxn],val[maxn];
bool vis[maxn];
vector<int> vec;
void getWC(int u,int ft){
    int mx=0;
    siz[u]=1;
    go(u,i){
        int t=e[i].to;
        if(t==ft||vis[t])   continue;
        getWC(t,u);
        siz[u]+=siz[t];
        mx=max(mx,siz[t]);
    }
    mx=max(mx,all-siz[u]);
    if(mx*2<=all)   rt=u;
}
void dfs(int u,int ft,int ff){
    siz[u]=1;
    bel[u]=ff;
    dep[u]=dep[ft]+1;
    if(ft)  vec.eb(u);
    go(u,i){
        int t=e[i].to;
        if(t==ft||vis[t])   continue;
        dfs(t,u,ff);
        siz[u]+=siz[t];
    }
}
void dfs2(int u,int ft,int ff){
    int L=max(l[u],l[ff]),R=min(r[u],r[ff]);
    if(L<=R)    madd(ans,1ll*dep[u]*a[ff]%mod*a[u]%mod*(R-L+1)%mod);
    go(u,i){
        int t=e[i].to;
        if(t==ft||vis[t])   continue;
        dfs2(t,u,ff);
    }
}
vector<int> b;
void discrete(){
    b.clear();
    for(int i:vec)    b.eb(l[i]),b.eb(r[i]+1);
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    for(int i:vec){
        int tl=lower_bound(b.begin(),b.end(),l[i])-b.begin()+1,tr=lower_bound(b.begin(),b.end(),r[i]+1)-b.begin()+1;
        ins[tl].eb(i);del[tr].eb(i);
    }
}
void divide(int u){
    // debug("u = %d\n",u);
    vec.clear();
    dep[u]=0;
    go(u,i){
        int t=e[i].to;
        if(vis[t])  continue;
        dfs(t,u,t);
    }
    dfs2(u,0,u);
    // debug("%d\n",immul(ans,ALL));
    discrete();
    int m=b.size(),tot=0,now=0,sl=0,sum=0;
    for(int i=1;i<=m;i++){
        for(int j:del[i]){
            mdel(val[bel[j]],immul(dep[j],a[j]));mdel(sum,immul(dep[j],a[j]));
            mdel(vl[bel[j]],a[j]);mdel(sl,a[j]);
            mdel(now,1ll*dep[j]*a[j]%mod*imdel(sl,vl[bel[j]])%mod);mdel(now,immul(a[j],imdel(sum,val[bel[j]])));
        }
        vector<int>().swap(del[i]);
        for(int j:ins[i]){
            madd(now,1ll*dep[j]*a[j]%mod*imdel(sl,vl[bel[j]])%mod);madd(now,immul(a[j],imdel(sum,val[bel[j]])));
            madd(val[bel[j]],immul(dep[j],a[j]));madd(sum,immul(dep[j],a[j]));
            madd(vl[bel[j]],a[j]);madd(sl,a[j]);
        }
        vector<int>().swap(ins[i]);
        // if(now) debug("%d %d %d\n",i,immul(now,ALL),b[i]-b[i-1]);
        if(now) madd(ans,immul(now,(b[i]-b[i-1])));
    }
    // debug("ans = %d\n",immul(ans,ALL));
    // for(int i=1;i<=n;i++)   assert(!vl[i]&&!val[i]);
    vis[u]=true;
    go(u,i){
        int t=e[i].to;
        if(vis[t])  continue;
        // debug("%d %d\n",t,siz[t]);
        all=siz[t];getWC(t,0);divide(rt);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&l[i],&r[i]);
    for(int i=1;i<=n;i++)   a[i]=qpow(r[i]-l[i]+1,mod-2),mmul(ALL,r[i]-l[i]+1);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    all=n;getWC(1,0);divide(rt);
    printf("%lld\n",immul(ALL,ans));
}