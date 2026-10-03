#include<bits/stdc++.h>
// #include "highway.h"
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
const int maxn=9e4+10,maxm=2.6e5+10;
int n,m;
namespace Graph{
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
ll ask(const vector<int>&w);
void answer(int s,int t);
ll dis;
bool vis[maxn];
vector<int> g[2][maxn];
int dp[2][maxn],rnk[2][maxn];
queue<int> que;
priority_queue<pii,vector<pii>,greater<pii>> q;
vector<int> all;
void dijkstra(int s,bool o){
    mems(dp[o],0x3f);mems(vis,0);
    q.ep(dp[o][s]=0,s);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=true;
        go(u,i){
            if(dp[o][t]>dp[o][u]+1){
                dp[o][t]=dp[o][u]+1;
                q.ep(dp[o][t],t);
            }
        }
    }
    for(int u=1;u<=n;u++){
        go(u,i)if(dp[o][u]==dp[o][t]+1){g[o][t].eb(u);break;}
    }
}
int solve(int s,bool o){
    int tot=0;
    que.ep(s);
    while(!que.empty()){
        int u=que.front();que.pop();
        rnk[o][++tot]=u;
        for(int t:g[o][u])if(dp[!o][t]==dp[o][t]+1)que.ep(t);
    }
    int l=1,r=tot,p=rnk[o][tot];
    while(l<=r){
        int mid=(l+r)>>1;
        vector<int> vec=all;
        for(int _=mid;_<=tot;_++){
            int u=rnk[o][_];
            go(u,i)vec[(i>>1)-1]=1;
        }
        if(ask(vec)==dis)   p=rnk[o][mid-1],r=mid-1;
        else    l=mid+1;
    }
    return p;
}
void find_pair(int N,vector<int> U,vector<int> V,int A,int B){
    n=N;m=U.size();
    for(int i=0;i<m;i++)    adde(U[i]+1,V[i]+1);
    dis=ask(vector<int>(m,0));
    int l=1,r=m-1,p=m;
    while(l<=r){
        int mid=(l+r)>>1;
        vector<int> res;
        for(int i=1;i<=mid;i++) res.eb(0);
        for(int i=mid+1;i<=m;i++)   res.eb(1);
        if(ask(res)==dis)   p=mid,r=mid-1;
        else l=mid+1;
    }
    for(int i=1;i<=p;i++)   all.eb(0);
    for(int i=p+1;i<=m;i++) all.eb(1);
    int s=U[p-1]+1,t=V[p-1]+1;
    dijkstra(s,0);dijkstra(t,1);
    answer(solve(s,0)-1,solve(t,1)-1);
}