#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1010;
const ll INF=2e18;
int n,m,Q;
const int maxm=2010;
#define go(o,x,i) for(ll i=G[o].head[x],t=G[o].e[i].to,l=G[o].e[i].l,r=G[o].e[i].r,w=G[o].e[i].w;i;i=G[o].e[i].nxt,t=G[o].e[i].to,l=G[o].e[i].l,r=G[o].e[i].r,w=G[o].e[i].w)
struct Graph{
    int cnt=1;
    int head[maxn];
    struct edge{ll nxt,to,l,r,w;}e[maxm];
    inline void add(ll u,ll v,ll l,ll r,ll w){e[++cnt]={head[u],v,l,r,w};head[u]=cnt;}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}G[2];
ll dp[2][maxn][maxm];
priority_queue<pli,vector<pli>,greater<pli>> q;
void bfs(int S,ll x,int id){
    dp[0][S][id]=x;q.ep(x,S);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        go(0,u,i){
            if(dp[0][u][id]>r) continue;
            if(dp[0][t][id]>max(dp[0][u][id],l)+w){
                dp[0][t][id]=max(dp[0][u][id],l)+w;
                q.ep(dp[0][t][id],t);
            }
        }
    }
}
void bfs2(int S,ll x,int id){
    dp[1][S][id]=x;q.ep(-x,S);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        go(1,u,i){
            if(dp[1][u][id]<l) continue;
            if(dp[1][t][id]<min(dp[1][u][id],r)-w){
                dp[1][t][id]=min(dp[1][u][id],r)-w;
                q.ep(-dp[1][t][id],t);
            }
        }
    }
}
int main(){
    mems(dp[0],0x3f);mems(dp[1],-0x3f);
    // freopen("path.in","r",stdin);freopen("path.out","w",stdout);
    scanf("%d%d",&n,&m);
    int S,T;scanf("%d%d",&S,&T);
    for(int i=1;i<=m;i++){
        int u,v;ll b,e,c;scanf("%d%d%lld%lld%lld",&u,&v,&b,&e,&c);
        if(b+c>e)   continue;
        G[0].add(u,v,b,e-c,c);
        G[1].add(v,u,b+c,e,c);
    }
    for(int i=1;i<=m;i++){
        int u=G[1].e[i+1].to,v=G[0].e[i+1].to;
        bfs(v,G[0].e[i+1].r+G[0].e[i+1].w,i);
        bfs2(u,G[1].e[i+1].r-G[1].e[i+1].w,i);
    }
    ll ans=INF;
    for(int i=1;i<=m;i++)   gmn(ans,dp[0][T][i]-dp[1][S][i]);
    if(ans==INF)puts("Impossible");
    else    printf("%lld\n",ans);
}