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
const int maxn=1e4+10;
int n;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    void rebuild(){cnt=1;mems(head,0);}
}
using namespace Graph;
int siz[maxn],ans[maxn],mxd[maxn];
int dep[maxn],f[maxn];  // dp[u][i] 表示 u 子树内有 i 个 1 的点时能覆盖的答案
vector<int> sum[maxn],dp[maxn];
inline void getmx(auto &x,auto y){(x<y)&&(x=y);}
void dfs(int u,int ft){
    siz[u]=1;
    mxd[u]=dep[u]=dep[ft]+1;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
        siz[u]+=siz[t];
        mxd[u]=max(mxd[u],mxd[t]);
    }
    sum[u].resize(mxd[u]+1);dp[u].resize(siz[u]+1);
    for(int i=dep[u];i<=mxd[u];i++)sum[u][i]=1;
    for(int i=0;i<=siz[u];i++)dp[u][i]=0;
    dp[u][1]=1;siz[u]=1;
    go(u,i){
        if(t==ft)   continue;
        for(int j=dep[t];j<=mxd[t];j++)  sum[u][j]+=sum[t][j];
        for(int j=mxd[t]+1;j<=mxd[u];j++)   sum[u][j]+=sum[t].back();   
        for(int j=0;j<=siz[u];j++)f[j]=dp[u][j];
        for(int j=1;j<=siz[u];j++){
            for(int k=1;k<=siz[t];k++){
                getmx(dp[u][j+k],f[j]+dp[t][k]);
            }
        }
        for(int j=1;j<=siz[u];j++)
            getmx(dp[u][j],f[j]+sum[t][min(mxd[t],dep[u]<<1)]);
        siz[u]+=siz[t];
        vector<int>().swap(sum[t]),vector<int>().swap(dp[t]);
    }
}
void matt(){
    rebuild();
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    for(int i=n;i;i--)
        for(int j=1;j<=dp[1][i];j++)    ans[j]=n-i+1;
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}