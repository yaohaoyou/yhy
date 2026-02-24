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
const int maxn=1010,maxk=5,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,k;
int dp[maxn][maxn][maxk][2][2];  // dp[u][i][j][0/1][0/1] 表示 b[u]=i 时，是/否存在 b[v]<b[u]，u 的颜色为 0/1，u 子树内的 sum(b[v])^j 的值
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
void dfs(int u,int ft){
    go(u,i)dfs(t,u);
    go(u,_){
        for(int i=2;i<=n;i++){
            auto t0=dp[t][i],t1=dp[t][i+1],tt=dp[t][i-1];
            madd(dp[u][i][1][0][0],(1ll*t1[1][0][0]+t0[1][1][0]+t1[1][1][0]+tt[1][1][0])%mod);
            madd(dp[u][i][2][0][0],(1ll*t1[1][0][0]));
        }
    }
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);add(x,i);}
    dfs(1,0);
}