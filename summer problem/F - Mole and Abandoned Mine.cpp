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
const int maxn=21,maxN=(1<<15)+10,INF=2e9;
map<pii,int> mp;
int n,m;
namespace Graph{
    const int maxm=maxn*maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
inline int lowbit(int x){return x&-x;}
int dp[2][maxN],f[maxN],g[maxN][maxn];
vector<int> v;
int main(){
    scanf("%d%d",&n,&m);
    const int N=(1<<n)-1;
    for(int i=1;i<=m;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(u,v,w);mp[{u,v}]=mp[{v,u}]=w;}
    for(int s=0;s<=N;s++){
        v.clear();
        {int x=s;while(x){v.eb(__lg(lowbit(x))+1);x^=lowbit(x);}}
        for(int u:v)go(u,i)if(!(s&(1<<t-1)))f[s]+=w;
    }
    mems(g,-0x3f);
    go(1,i) g[1<<t-1][t]=w;
    int ans=INF;
    for(int s=0;s<=N;s++)if((s&1)&&(s&(1<<n-1))){
        v.clear();
        {int x=s;while(x){v.eb(__lg(lowbit(x))+1);x^=lowbit(x);}}
        int sum=-INF;
        {
            int S=s^1^(1<<n-1);
            if(!S)  sum=g[1<<n-1][n];
            for(int u:v){
                if(u==1||u==n)  continue;
                go(u,_){
                    if(t==1||t==n||t==u||!(S&(1<<t-1)))  continue;
                    g[S][u]=max(g[S][u],g[S^(1<<u-1)][t]+w);
                }
                if(mp.find(pii(u,n))!=mp.end()) sum=max(sum,g[S][u]+mp[{u,n}]);
            }
        }
        if(sum==-INF)    continue;
        int ppc=__builtin_popcount(s);
        mems(dp,0x3f);
        dp[0][0]=0;
        int x=N^s;
        for(int k=1;k<=ppc;k++){
            int w=1<<v[k-1]-1;
            for(int i=x;1;i=(i-1)&x){
                dp[k&1][i]=INF;
                int y=x^i;
                for(int j=y;1;j=(j-1)&y){
                    dp[k&1][i|j]=min(dp[k&1][i|j],dp[(k-1)&1][i]+f[j|w]);
                    if(!j)  break;
                }
                if(!i)  break;
            }
        }
        ans=min(ans,(dp[ppc&1][x]>>1)-sum);
    }
    printf("%d\n",ans);
}