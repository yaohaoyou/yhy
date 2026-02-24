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
const int maxn=1e4+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
inline void gmx(int &x,int y){(x<y)&&(x=y);}
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(ll &x,ll y){(x<y)&&(x=y);}
inline void gmn(ll &x,ll y){(x>y)&&(x=y);}
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int T,n;
int a[maxn],W[maxn],V[maxn],mx[maxn];
ll dp[maxn][maxn];
void dfs(int u,int ft){
    mx[u]=V[u];
    mems(dp[u],0);
    go(u,i){
        if(t==ft)    continue;
        dfs(t,u);
        gmx(mx[u],mx[t]);
        for(int j=V[u];j<=mx[t];j++)   dp[u][j]+=dp[t][j];
    }
    for(int i=mx[u]-1;i>=V[u];i--)    gmn(dp[u][i],dp[u][i+1]+W[u]);
    for(int i=V[u]-1;~i;i--)    dp[u][i]=dp[u][i+1]+W[u];
    for(int i=mx[u]-1;i;i--)    printf("%lld ",dp[u][i]-dp[u][i+1]);puts("");
}
void matt(){
    dfs(1,0);
    int ans=1;
    for(int i=1;i<=n;i++)   mmul(ans,dp[i][0]%mod);
    printf("%d\n",ans);
}
int main(){
    scanf("%d%d",&T,&n);T--;
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    for(int i=1;i<=n;i++)   scanf("%d",&W[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&V[i]);
    matt();
    while(T--){
        int k;scanf("%d",&k);
        while(k--){int x;scanf("%d",&x);swap(W[x],W[x+1]);}
        matt();
    }
}