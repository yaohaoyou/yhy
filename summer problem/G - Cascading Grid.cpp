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
const int maxn=50,inf=1e9;
int n,m,S,T;
int tot;
char a[maxn][maxn];
int id[maxn][maxn];
namespace Graph{
    const int maxp=maxn*maxn,maxm=maxp*10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    #define gonow(x,i) for(int i=now[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxp],now[maxp];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,0);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
queue<int> q;
int dep[maxp];
bool bfs(){
    queue<int>().swap(q);
    mems(dep,0);memc(now,head);
    q.ep(S);dep[S]=1;
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
int dfs(int u,int flw){
    if(u==T)    return flw;
    int res=flw;
    gonow(u,i)if(w&&dep[t]==dep[u]+1){
        now[u]=i;
        int d=dfs(t,min(res,w));
        if(!d)  dep[t]=0;
        e[i].w-=d;e[i^1].w+=d;res-=d;
        if(!res)    break;
    }
    return flw-res;
}
int dinic(){
    int res=0;
    while(bfs())res+=dfs(S,inf);
    return res;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%s",a[i]+1);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]!='#')id[i][j]=++tot;
    S=0;T=++tot;
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)if(a[i][j]!='#'){
            adde(id[i][j],T,1);
            adde(S,id[i][j],a[i][j]=='+'?0:2);
            ans++;
        }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(a[i][j]!='#'){
            // int x=j+1;while(x<=m&&a[i][x]!='#')adde(id[i][j],id[i][x],inf),x++;
            // x=j-1;while(x&&a[i][x]!='#')adde(id[i][j],id[i][x],inf),x--;
            // x=i+1;while(x<=n&&a[x][j]!='#')adde(id[i][j],id[x][j],inf),x++;
            if(j<m&&a[i][j+1]!='#')adde(id[i][j],id[i][j+1],inf);
            if(j>1&&a[i][j-1]!='#')adde(id[i][j],id[i][j-1],inf);
            if(i<n&&a[i+1][j]!='#')adde(id[i][j],id[i+1][j],inf);
        }
    }
    printf("%d\n",ans-dinic());
}