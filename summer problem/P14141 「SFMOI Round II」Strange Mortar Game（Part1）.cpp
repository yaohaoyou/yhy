#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e3+10,maxp=maxn*maxn,dir[2][2]={{1,0},{0,-1}};
int n,m,k,tot;
int id[maxn][maxn],idx[maxp],idy[maxp];
namespace Graph{
    const int maxm=maxp*10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to,w,id;}e[maxm];
    inline void add(int u,int v,int w,int id){e[++cnt]={head[u],v,w,id};head[u]=cnt;}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
priority_queue<pli,vector<pli>,greater<pli>> q;
ll dis[maxp];bool vis[maxp],out[maxn][maxn<<1];
pii fr[maxp];
void dijkstra(){
    mems(dis,0x3f);
    for(int i=1;i<=n;i++)   q.ep(dis[id[i][1]]=0,id[i][1]);
    for(int i=1;i<=m;i++)   q.ep(dis[id[n][i]]=0,id[n][i]);
    while(!q.empty()){
        int u=q.top().se;q.pop();if(vis[u])continue;vis[u]=true;
        go(u,i)if(dis[t]>dis[u]+w){fr[t]=pii(u,e[i].id);dis[t]=dis[u]+w;q.ep(dis[t],t);}
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<=n;i++)for(int j=1;j<=m+1;j++)id[i][j]=++tot,idx[tot]=i,idy[tot]=j;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)for(int o:{0,1}){
        int x=i+dir[o][0],y=j+dir[o][1];
        if(x>0&&x<=n&&y>0&&y<=m)    add(id[i][j],id[x][y],0,0),printf("%d,%d %d,%d\n",i,j,x,y);
    }
    for(int i=1;i<=k;i++){
        int lx,rx,ly,ry;scanf("%d%d%d%d",&lx,&ly,&rx,&ry);
        int w=(rx-lx+1)*(ry-ly+1);
        for(int j=max(3,lx+ly);j<=rx+ry&&j<n+m;j++){
            int sx=min(rx,j-ly),sy=j-sx,ty=min(ry,j-lx)+1,tx=j-ty;
            printf("%d,%d %d,%d\n",sx,sy,tx,ty);
            add(id[sx][sy],id[tx][ty],w,i);
        }
    }
    dijkstra();
    pli ans=pli(1e18,0);
    for(int i=0;i<=n;i++)ans=min(ans,pli(dis[id[i][m+1]],id[i][m+1]));
    for(int i=1;i<=m+1;i++)ans=min(ans,pli(dis[id[0][i]],id[0][i]));
    if(ans.fi==1e18)   return puts("Impossible!"),0;
    else printf("%lld\n",ans.fi);
    int u=ans.se;
    while(u){
        int x=idx[u],y=idy[u];
        if(fr[u].se)    out[fr[u].se][x+y-2]=true;
        u=fr[u].fi;
    }
    for(int i=1;i<=k;i++,puts(""))for(int j=1;j<=n+m-2;j++)printf("%d ",out[i][j]);
}