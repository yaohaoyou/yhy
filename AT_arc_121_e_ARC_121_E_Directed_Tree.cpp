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
const int maxn=2010,mod=998244353;
int n;
int p[maxn];
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
int siz[maxn];
int dp[maxn][maxn][2];  // dp[u][i][0/1] 
void dfs(int u,int ft){
    int f[maxn][2];
    siz[u]=1;
    dp[u][0][0]=1;
    go(u,o){
        if(t==ft)   continue;
        dfs(t,u);
        for(int i=0;i<=siz[u]+siz[t];i++)   f[i][0]=f[i][1]=0;
        for(int i=0;i<=siz[u];i++){
            for(int j=0;j<=siz[t];j++){
                int sum=imadd(dp[t][j][0],dp[t][j][1]);
                madd(f[i+j][0],immul(dp[u][i][0],sum));
                madd(f[i+j][1],immul(dp[u][i][1],sum));
                if(j^siz[t])madd(f[i+j+1][1],immul(dp[u][i][0],immul(sum,siz[t]-j)));
            }
        }
        siz[u]+=siz[t];
        for(int i=0;i<=siz[u];i++)  dp[u][i][0]=f[i][0],dp[u][i][1]=f[i][1];
    }
    // printf("dp[%d] : ",u);for(int i=0;i<=siz[u];i++)  printf("(%d,%d) ",dp[u][i][0],dp[u][i][1]);puts("");
}
int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    dfs(1,0);
    int ans=0,fac=1;
    for(int i=n;~i;i--){
        if(n^i) mmul(fac,n-i);
        int s=immul(imadd(dp[1][i][0],dp[1][i][1]),fac);
        if(!(i&1)) madd(ans,s);
        else mdel(ans,s);
    }
    printf("%d\n",ans);
}