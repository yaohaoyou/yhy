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
const int maxn=5010<<2,inf=1e9;
int n,m,k,V,S,T;
int a[maxn],b[maxn],c[maxn],id[maxn];
int pre[maxn],suf[maxn];
namespace Graph{
    const int maxm=maxn<<2;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    #define gonow(x,i) for(int i=now[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn],now[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,0);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
queue<int> q;
int d[maxn];
bool bfs(){
    queue<int>().swap(q);
    mems(d,-1);memc(now,head);
    d[S]=0;q.ep(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        go(u,i){
            if(~d[t]||!w)  continue;
            d[t]=d[u]+1;
            if(t==T)    return true;
            q.ep(t);
        }
    }
    return false;
}
int dfs(int u,int flw){
    if(u==T)    return flw;
    int res=flw;
    gonow(u,i){
        if(!w||d[t]^(d[u]+1))   continue;
        int fl=dfs(t,min(w,res));
        e[i].w-=fl;e[i^1].w+=fl;res-=fl;
        if(!fl) d[t]=-1;
        if(!res)    break;
    }
    return flw-res;
}
ll dinic(){
    ll flow=0;
    while(bfs())    flow+=dfs(S,inf);
    return flow;
}
int main(){
    // freopen("D:\\yhy\\ZROI\\summer\\day10\\exhibition\\exhibition7.in","r",stdin);
    // freopen("exhibition.in","r",stdin);freopen("exhibition.out","w",stdout);
    scanf("%d%d%d%d",&n,&m,&k,&V);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m-k+1;i++)   scanf("%d",&c[i]);
    int tot=n;
    for(int i=1;i<=n;i++)   adde(S,i,V-b[i]);
    for(int i=1;i<=m;i++){
        pre[i]=++tot;
        // printf("i = %d %d\n",i,a[i]);
        if(i!=1&&i%k!=1)  adde(pre[i-1],pre[i],inf);
        adde(a[i],pre[i],inf);
    }
    for(int i=m;i;i--){
        suf[i]=++tot;
        if(i!=m&&i%k)  adde(suf[i+1],suf[i],inf);
        adde(a[i],suf[i],inf);
    }
    T=++tot;
    ll ans=0;
    for(int i=1;i<=m-k+1;i++){
        int l=i,r=i+k-1; 
        id[i]=++tot;
        // debug("%d %d %d %d\n",l,i,suf[l],id[i]);
        adde(suf[l],id[i],inf);
        if((l-1)/k!=(r-1)/k)  adde(pre[r],id[i],inf);
        adde(id[i],T,c[i]);ans+=c[i];
    }
    printf("%lld\n",ans-dinic());
}