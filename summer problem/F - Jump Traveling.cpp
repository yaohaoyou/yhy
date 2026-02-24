#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,maxk=22;
int n,k;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){cnt=1;for(int i=1;i<=n;i++)head[i]=0;}
}
using namespace Graph;
int ans[maxn],pas[maxn][maxk];
unordered_map<int,int> dp[maxn][maxk];  // dp[u][i][j] 表示 u 从 j 到达，当前步数为 i 的答案。
queue<piii> q;
void bfs(){
    dp[1][0][0]=0;
    q.ep(1,pii(0,0));
    while(!q.empty()){
        auto [u,tmp]=q.front();q.pop();auto [i,j]=tmp;
        pas[u][i]++;if(pas[u][i]>2) continue;
        int o=dp[u][i][j];
        if(!i)  ans[u]=(~ans[u])?min(ans[u],o):o;
        // printf("%d %d %d : %d\n",u,i,j,o);
        go(u,l){
            int t=e[l].to;
            if(t==j)    continue;
            if(i+1==k){
                if(dp[t][0].find(0)==dp[t][0].end()||dp[t][0][0]>o+1){dp[t][0][0]=o+1;q.ep(t,pii(0,0));}
            }
            else if(dp[t][i+1].find(u)==dp[t][i+1].end()||dp[t][i+1][u]>o){dp[t][i+1][u]=o;q.ep(t,pii(i+1,u));}
        }
    }
}
void matt(){
    rebuild();
    for(int i=1;i<=n;i++)for(int j=0;j<=k;j++)dp[i][j].clear(),pas[i][j]=0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++)ans[i]=-1;
    bfs();
    for(int u=2;u<=n;u++)   printf("%d ",ans[u]);
    puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}