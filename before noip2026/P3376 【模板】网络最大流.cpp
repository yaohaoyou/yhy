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
const int maxn=210,maxm=10010;
const ll INF=1e18;
int n,m,S,T;
namespace Graph{
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
int dep[maxn];
queue<int> q;
bool bfs(){
    while(!q.empty())q.pop();
    cpy(now,head,n);fll(dep,0,n);
    dep[S]=1;q.ep(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        go(u,i)if(w&&!dep[t]){
            dep[t]=dep[u]+1;
            if(t==T)    return true;
            q.ep(t);
        }
    }
    return false;
}
ll dfs(int u,ll fl){
    if(u==T)    return fl;
    ll res=fl;
    gonow(u,i)if(dep[t]==dep[u]+1&&w){
        now[u]=i;
        ll d=dfs(t,min(res,(ll)w));
        if(!d)  dep[t]=-1;
        res-=d;e[i].w-=d;e[i^1].w+=d;
    }
    return fl-res;
}
ll dinic(){ll res=0;while(bfs())res+=dfs(S,INF);return res;}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);}
    printf("%lld\n",dinic());
}