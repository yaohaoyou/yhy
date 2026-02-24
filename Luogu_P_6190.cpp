#pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define int long long
#define mem(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=110,maxm=2510;
int n,m,k;
inline void getmn(int &x,int y){(x>y)&&(x=y);}
inline void getmx(int &x,int y){(x<y)&&(x=y);}
namespace Graph{
    int cnt;
    int head[maxn];
    struct edge{int nxt,fr,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],u,v,w};head[u]=cnt;}
}
using namespace Graph;
struct Matrix{
    int dp[maxn][maxn];  // dp[i][j] 表示使用了至多 x 次魔法，从 i 到 j 的最短路
    inline Matrix operator*(const Matrix &x){
        Matrix res;
        mem(res.dp,0x3f);
        #pragma unroll(4)
        for(int i=1;i<=n;i++)
        #pragma unroll(4)
            for(int j=1;j<=n;j++){
        #pragma unroll(4)
                for(int k=1;k<=m;k++)
                    getmn(res.dp[i][j],dp[i][e[k].fr]+x.dp[e[k].to][j]-e[k].w);
                getmn(res.dp[i][j],dp[i][j]);getmn(res.dp[i][j],x.dp[i][j]);
            }
        return res;
    }
    inline void print(){
        for(int i=1;i<=n;i++,puts(""))
            for(int j=1;j<=n;j++)   printf("%lld ",dp[i][j]);
        puts("");
    }
};
Matrix base,ans;
inline Matrix qpow(Matrix x,int y){
    Matrix res=base;
    #pragma unroll(4)
    while(y){
        if(y&1) res=res*x;
        x=x*x;
        y>>=1;
    }
    return res;
}
signed main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    mem(base.dp,0x3f);
    for(int i=1;i<=n;i++) base.dp[i][i]=0;
    for(int i=1,u,v,w;i<=m;i++){
        scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
        getmn(base.dp[u][v],w);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)   getmn(base.dp[i][j],base.dp[i][k]+base.dp[k][j]);
    ans=qpow(base,k);
    printf("%lld\n",ans.dp[1][n]);
}