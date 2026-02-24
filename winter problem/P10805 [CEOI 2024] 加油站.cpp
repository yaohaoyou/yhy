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
const int maxn=7e4+10;
int n,k;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void upd(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){upd(u,v,w);upd(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
// struct BIT{
const int K=1e9+5;
const ll N=1e9*7e4+10;
//     unordered_map<ll,ll> tr;
//     inline ll lowbit(ll x){return x&-x;}
//     inline void upd(ll x,int s){if(!s)return;x+=K;if(s>0){while(x<=N){tr[x]+=s;x+=lowbit(x);}}else{while(x<=N){!(tr[x]+=s)&&(tr.erase(x));x+=lowbit(x);}}}
//     inline ll que(ll x){x+=K;ll res=0;while(x){if(tr.find(x)!=tr.end())res+=tr[x];x^=lowbit(x);}return res;}
//     inline ll query(ll l,ll r){return l>r?0:que(r)-que(l-1);}
//     void clear(){tr.clear();}
// }T;
const int maxp=maxn*50;
struct SegmentTree{
    #define lson lc[p],l,mid
    #define rson rc[p],mid+1,r
    #define setmid ll mid=(l+r)>>1
    #define setpos int &p,ll l,ll r
    int tot,rt;
    int lc[maxp],rc[maxp],tr[maxp];
    inline void pu(int p){tr[p]=(lc[p]?tr[lc[p]]:0)+(rc[p]?tr[rc[p]]:0);}
    void upd(setpos,ll x,int s){if(!p)p=++tot,tr[p]=lc[p]=rc[p]=0;if(l==r)return tr[p]+=s,void();setmid;(x<=mid)?upd(lson,x,s):upd(rson,x,s);pu(p);}
    int query(setpos,ll pl,ll pr){if(!p)return 0;if(l>=pl&&r<=pr)return tr[p];setmid;int res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res+=query(rson,pl,pr);return res;}
    void clear(){rt=tot=0;}
}T;
bool vis[maxn];
int siz[maxn],fa[20][maxn],f[maxn];
ll ans[maxn],dep[maxn];
int rt,all;
vector<int> V;
#define __div(x,y) all=y,getWC(x,0),divide(rt);
void getWC(int u,int ft){
    int mx=0;
    siz[u]=1;
    go(u,i)if((t^ft)&&!vis[t]){
        getWC(t,u);
        siz[u]+=siz[t];
        mx=max(mx,siz[t]);
    }
    mx=max(mx,all-siz[u]);
    if(2*mx<=all)    rt=u;
}
void dfs(int u,int ft){
    V.eb(u);
    fa[0][u]=ft;
    siz[u]=1;
    go(u,i)if((t^ft)&&!vis[t]){dep[t]=dep[u]+w;dfs(t,u);siz[u]+=siz[t];}
}
void dfs2(int u,int ft){
    int x=u;
    for(int i=19;~i;i--)if(dep[u]-dep[fa[i][x]]<=k)x=fa[i][x];
    f[u]=1;
    go(u,i)if((t^ft)&&!vis[t])dfs2(t,u);
    if(x^rt)   f[x]+=f[u];
    T.upd(T.rt,-K,N,-dep[u],f[u]);
    ans[u]+=1ll*(f[u]-1)*all;
}
void ins(int u,int ft){T.upd(T.rt,-K,N,-dep[u],f[u]);go(u,i)if((t^ft)&&!vis[t])ins(t,u);}
void era(int u,int ft){T.upd(T.rt,-K,N,-dep[u],-f[u]);go(u,i)if((t^ft)&&!vis[t])era(t,u);}
void dfs4(int u,int ft){
    go(u,i)if((t^ft)&&!vis[t]){
        // dep[u]-k<=dep[x]<=w-k-1+dep[u]
        int x=T.query(T.rt,-K,N,dep[u]-k,w-1+dep[u]-k);
        ans[u]+=1ll*x*siz[t];
        T.upd(T.rt,-K,N,dep[u],x);
        dfs4(t,u);
        T.upd(T.rt,-K,N,dep[u],-x);
    }
}
void divide(int u){
    V.clear();dep[u]=0;dfs(u,0);vis[u]=true;all=siz[u];
    for(int i=1;i<20;i++)for(int j:V)fa[i][j]=fa[i-1][fa[i-1][j]];
    f[u]=1;
    T.clear();
    go(u,i)if(!vis[t]){
        all=siz[u]-siz[t];
        dfs2(t,0);
    }
    go(u,i)if(!vis[t]){
        era(t,u);
        int x=T.query(T.rt,-K,N,dep[u]-k,w-1+dep[u]-k);
        ans[u]+=1ll*x*siz[t];
        T.upd(T.rt,-K,N,dep[u],x+1);
        dfs4(t,u);
        T.upd(T.rt,-K,N,dep[u],-x-1);
        ins(t,u);
    }
    go(u,i)if(!vis[t])__div(t,siz[t]);
}
int main(){
    freopen("stations.in","r",stdin);freopen("stations.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(++u,++v,w);}
    __div(1,n);
    for(int i=1;i<=n;i++)   printf("%lld\n",ans[i]);
}