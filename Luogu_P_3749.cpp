#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=110,maxp=maxn*maxn+1010,inf=0x3f3f3f3f,dir[8][2]={{3,1},{-3,1},{3,-1},{-3,-1},{1,3},{1,-3},{-1,3},{-1,-3}};
int n;bool m;
int a[maxn],c[maxn][maxn];
namespace Graph{
    const int maxm=maxp<<4;
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
    T=1;tot=1;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++){
            scanf("%d",&c[i][j]);
            id[i][j]=++tot;
        }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(i==j){
                if(m)   adde(id[i][j],tot+a[i],inf);
                c[i][j]-=a[i];
            }
            else{
                adde(id[i][j],id[i+1][j],inf);
                adde(id[i][j],id[i][j-1],inf);
            }
            if(c[i][j]>=0)  adde(S,id[i][j],c[i][j]),sum+=c[i][j];
            else    adde(id[i][j],T,-c[i][j]);
        }
    }
    if(m){
        for(int i=1;i<=1000;i++){
            tot++;
            adde(tot,T,i*i*m);
        }
    }
    printf("%d\n",sum-dinic());
}