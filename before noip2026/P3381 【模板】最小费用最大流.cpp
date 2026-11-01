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
const int maxn=5e3+10,maxm=1e5+10,inf=1e9;
int n,m,S,T;
namespace Graph{
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
int dep[maxn];
bool inq[maxn],vis[maxn];
queue<int> q;
bool bfs(){
    while(!q.empty())q.pop();
    cpy(now,head,n);fll(dep,inf,n);fll(inq,0,n);fll(vis,0,n);
    dep[S]=0;q.ep(S);
    while(!q.empty()){
        int u=q.front();q.pop();inq[u]=false;
        go(u,i)if(w&&dep[t]>dep[u]+c){
            dep[t]=dep[u]+c;
            if(!inq[t]) q.ep(t),inq[t]=true;
        }
    }
    return dep[T]<dep[0];
}
int cost;
int dfs(int u,int fl){
    if(u==T)    return fl;
    vis[u]=true;
    int res=fl;
    gonow(u,i)if(dep[t]==dep[u]+c&&w&&!vis[t]){
        now[u]=i;
        int d=dfs(t,min(res,(int)w));
        if(!d)  dep[t]=-1;
        else{
            res-=d;e[i].w-=d;e[i^1].w+=d;
            cost+=d*c;
        }
    }
    return fl-res;
}
int dinic(){
    int res=0;
    while(bfs())res+=dfs(S,inf);
    return res;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1;i<=m;i++){int u,v,w,co;scanf("%d%d%d%d",&u,&v,&w,&co);adde(u,v,w,co);}
    printf("%d ",dinic());printf("%d\n",cost);
}