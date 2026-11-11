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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=4e5+10,inf=1e9;
int n,m,k;
int tot,S,T;
pii a[maxn],b[maxn];
int L[maxn],R[maxn],I[maxn],O[maxn];
namespace Graph{
    const int maxm=2e6+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w,c=e[i].c;i;i=e[i].nxt,t=e[i].to,w=e[i].w,c=e[i].c)
    #define gonow(x,i) for(int i=now[x],t=e[i].to,w=e[i].w,c=e[i].c;i;i=e[i].nxt,t=e[i].to,w=e[i].w,c=e[i].c)
    int cnt=1;
    int head[maxn],now[maxn];
    struct edge{int nxt,to,w,c;}e[maxm];
    inline void add(int u,int v,int w,int c){e[++cnt]={head[u],v,w,c};head[u]=cnt;}
    inline void adde(int u,int v,int w,int c){add(u,v,w,c);add(v,u,0,-c);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
ll h[maxn],d[maxn];
int pre[maxn];

bool dijkstra(){
    mems(d,0x3f);mems(pre,0);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> q;
    d[S]=0;q.ep(0,S);
    while(!q.empty()){
        auto [du,u]=q.top();q.pop();
        if(du!=d[u]) continue;
        go(u,i){
            if(!w) continue;
            ll nw=du+c+h[u]-h[t];
            if(d[t]>nw){
                d[t]=nw;pre[t]=i;
                q.ep(d[t],t);
            }
        }
    }
    if(d[T]==d[tot+1]) return false;
    for(int i=0;i<=tot;i++)
        if(d[i]!=d[tot+1]) h[i]+=d[i];
    return true;
}
ll cost;
ll MCMF(){
    int fl=0;
    while(dijkstra()){
        int now=inf;
        ll pathCost=0;
        for(int u=T;u^S;u=e[pre[u]^1].to){
            now=min(now,e[pre[u]].w);
            pathCost+=e[pre[u]].c;
        }
        for(int u=T;u^S;u=e[pre[u]^1].to){
            e[pre[u]].w-=now;
            e[pre[u]^1].w+=now;
        }

        fl+=now;
        cost+=1ll*now*pathCost;
    }

    assert(fl==k);
    return cost;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    for(int i=1;i<=m;i++)   scanf("%d%d",&b[i].fi,&b[i].se);
    sort(a+1,a+n+1,greater<pii>());
    {
        int N=0;
        for(int i=1,mx=-1;i<=n;i++){
            if(a[i].se>mx)  a[++N]=a[i];
            gmx(mx,a[i].se);
        }
        n=N;
        reverse(a+1,a+n+1);
    }
    for(int i=1;i<=n;i++){
        L[i]=++tot;
        if(i^1) adde(L[i-1],L[i],k,a[i-1].se-a[i].se),adde(L[i],L[i-1],k,0);
    }
    for(int i=1;i<=n+1;i++) R[i]=++tot;
    for(int i=n;i;i--){
        adde(R[i],R[i+1],k,a[i].fi-a[i-1].fi),adde(R[i+1],R[i],k,0);
        adde(R[i],L[i],k,0);
    }
    S=0;T=++tot;
    adde(S,L[1],k,0);adde(R[n+1],T,k,0);
    for(int i=1;i<=m;i++){
        int x=b[i].fi,p=lower_bound(a+1,a+n+1,pii(x,0))-a;
        I[i]=++tot;O[i]=++tot;adde(I[i],O[i],1,0);
        if(p<=n)    adde(O[i],R[p+1],1,a[p].fi-x);
        if(p)   adde(O[i],R[p],1,0);

        x=b[i].se;int l=1,r=n;p=0;while(l<=r){int mid=(l+r)>>1;if(a[mid].se>=x)p=mid,l=mid+1;else r=mid-1;}
        if(p)   adde(L[p],I[i],1,a[p].se-x);
        if(p^n) adde(L[p+1],I[i],1,0);
    }
    printf("%lld\n",MCMF());
}