#include<bits/stdc++.h>
using namespace std;
const int maxn=120,maxp=maxn*maxn,inf=0x3f3f3f3f;
int n,m;
namespace Graph{
    const int maxm=maxp<<3;
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to,w,c;}e[maxm];
    inline void add(int u,int v,int w,int c){e[++cnt]={head[u],v,w,c};head[u]=cnt;}
    inline void adde(int u,int v,int w,int c){add(u,v,w,c);add(v,u,0,-c);}
}
using namespace Graph;
int S,T;
queue<int> q;
bool inque[maxp];
int lst[maxp],lsti[maxp],d[maxp],flw[maxp];
bool bfs(){
    q.push(S);inque[S]=true;
    memset(d,0x3f,sizeof(d));memset(flw,0x3f,sizeof(flw));
    d[S]=lst[T]=0;
    while(!q.empty()){
        int u=q.front();
        inque[u]=false;
        q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(e[i].w&&d[u]+e[i].c<d[t]){
                flw[t]=min(e[i].w,flw[u]);
                d[t]=d[u]+e[i].c;
                lst[t]=u;lsti[t]=i;
                if(!inque[t]){q.push(t);inque[t]=true;}
            }
        }
    }
    return lst[T];
}
int MFMC(){
    int cost=0;
    while(bfs()){
        cost+=(flw[T]*d[T]);
        for(int p=T;p!=S;p=lst[p]){
            e[lsti[p]].w-=flw[T];e[lsti[p]^1].w+=flw[T];
        }
    }
    return -cost;
}
int tot;
int a[maxn][maxn],id[maxn][maxn];
int main(){
    scanf("%d%d",&n,&m);
    S=0;T=n*n*2+1;int p=n*n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
            id[i][j]=++tot;
        }
    adde(S,id[1][1],m,0);
    adde(id[n][n]+p,T,m,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            adde(id[i][j],id[i][j]+p,1,-a[i][j]);
            adde(id[i][j],id[i][j]+p,inf,0);
            int x=i+1,y=j;
            if(x<=n)    adde(id[i][j]+p,id[x][y],inf,0);
            x=i;y=j+1;
            if(y<=n)    adde(id[i][j]+p,id[x][y],inf,0);
        }
    }
    printf("%d",MFMC());
}