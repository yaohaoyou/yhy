#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=110,maxp=maxn*maxn,inf=0x3f3f3f3f,dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int n,m;
int a[maxn][maxn];
namespace Graph{
    const int maxm=maxp<<3;
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,0);}
}
using namespace Graph;
int d[maxp],now[maxp];
int S,T;
queue<int> q;
inline bool bfs(){
    while(!q.empty())   q.pop();
    memset(d,0x3f,sizeof(d));
    memcpy(now,head,sizeof(head));
    d[0]=0;
    q.push(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(d[t]!=inf||e[i].w<=0)  continue;
            d[t]=d[u]+1;
            q.push(t);
            if(t==T)    return true;
        }
    }
    return false;
}
int dfs(int u,int flw){
    if(u==T)    return flw;
    int res=0;
    for(int i=now[u];i&&flw;i=e[i].nxt){
        now[u]=i;
        int t=e[i].to;
        if(d[t]!=d[u]+1||!e[i].w)    continue;
        int k=dfs(t,min(e[i].w,flw));
        if(!k)  d[t]=inf;
        e[i].w-=k;e[i^1].w+=k;
        res+=k;flw-=k;
    }
    return res;
}
int dinic(){
    int ans=0;
    while(bfs())    ans+=dfs(S,inf);
    return ans;
}
int tot=0;
int id[maxn][maxn];
int main(){
    int sum=0;
    scanf("%d%d",&n,&m);
    T=n*m+1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);sum+=a[i][j];
            id[i][j]=++tot;
            if((i+j)&1){adde(S,id[i][j],a[i][j]);adde(id[i][j],T,0);}
            else{adde(S,id[i][j],0);adde(id[i][j],T,a[i][j]);}
        }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int o=0;o<4;o++){
                int x=i+dir[o][0],y=j+dir[o][1];
                if(x<=0||x>n||y<=0||y>m)    continue;
                if((i+j)&1) adde(id[i][j],id[x][y],inf);
            }
        }
    }
    printf("%d\n",sum-dinic());
}