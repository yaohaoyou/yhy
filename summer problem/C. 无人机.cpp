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
using namespace std;
const int maxn=2e5+10;
int n,m;
int a[maxn],b[maxn];
vector<int> buc[maxn];
namespace Graph{
    const int maxm=8e5+10;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int dp[2][maxn];
int clr[maxn],cl;
bool vis[maxn];
priority_queue<pii,vector<pii>,greater<pii>> q;
void dijkstra(int s,bool o){
    q.ep(0,s);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=true;clr[++cl]=u;
        if((!o&&u==n)||(o&&u==1))    continue;
        go(u,i){
            int t=e[i].to;
            dp[o][t]=max(dp[o][t],a[t]);
            if(dp[o][t]>dp[o][u]+1){dp[o][t]=max(a[t],dp[o][u]+1);q.ep(dp[o][t],t);}
        }
    }
    for(int i=1;i<=cl;i++)  vis[clr[i]]=false;
    cl=0;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);b[i]=a[i];}
    for(int i=1,u,v;i<=m;i++){scanf("%d%d",&u,&v);adde(u,v);}
    sort(b+1,b+n+1);int siz=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)   buc[lower_bound(b+1,b+siz+1,a[i])-b].eb(i);
    mems(dp,0x3f);dp[0][1]=dp[1][n]=0;
    int ans=1e9;
    dijkstra(1,0);dijkstra(n,1);
    for(int i=1;i<=n;i++)   ans=min(ans,max(dp[0][i],dp[1][i])<<1);
    for(int u=1;u<=n;u++)go(u,i)ans=min(ans,max(dp[0][u],dp[1][e[i].to])<<1|1);
    printf("%d\n",ans);
}