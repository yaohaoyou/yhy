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
const int maxn=1e5+10,maxk=31;
bool mem1;
int n,k;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
int f[maxn][maxk][2],mx[maxn][maxk][2];
inline pii fs(int x,int y,int z){
    if(x>z) return pii(x,max(y,z));
    return pii(z,x);
}
inline pii fs(int x,int y,int z,int w){
    if(x>z) return pii(x,max(y,z));
    return pii(z,max(x,w));
}
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int mg1[maxk][maxk],mg2[maxk][maxk],ff[maxk][maxk];
vector<vector<int>> g;
// inline int f(int u,int i){return max(max(dp[u][i][0],dp[u][i][1]),max(dp[u][i][2],dp[u][i][3]));}
void dfs(int u,int ft){
    vector<vector<int>> dp;dp.resize(k+1);for(int i=0;i<=k;i++)dp[i].resize(k+1,-1e9);
    mems(f[u],-0x3f);
    dp[0][0]=0;f[u][1][0]=0;
    go(u,_){
        if(t==ft)   continue;
        dfs(t,u);
        g=dp;//mems(dp[u],-0x3f);
        memc(ff,f[u]);//mems(f[u],-0x3f);
        for(int i=0;i<k;i++){
            mg1[0][i]=g[0][i];
            for(int j=1;j<k;j++)mg1[j][i]=max(mg1[j-1][i],g[j][i]);
            mg2[i][0]=g[i][0];
            for(int j=1;j<k;j++)mg2[i][j]=max(mg2[i][j-1],g[i][j]);
        }
        for(int j=0;j<k;j++)for(int p=0;j+p<k;p++)gmx(dp[p][j],g[0][j]+max(f[t][p][0],f[t][p][1]));
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                gmx(dp[i][j],g[i][j]+max(mx[t][min({k-i-1,k-j-1,j})][0],mx[t][min({k-i-1,k-j-1,j})][1]));
                gmx(f[u][max(i,j)+1][0],g[i][j]+max(mx[t][min(k-i-1,k-j-1)][0],mx[t][min(k-i-1,k-j-1)][1]));
                if(i)gmx(dp[i][j],g[i][j]+mx[t][min(i,k-j-1)][1]-1);
            }
        }
        for(int i=0;i<k;i++){
            for(int j=0;i+j<k;j++){
                gmx(dp[i][j],mg2[i][min(k-j-1,j)]+max(f[t][j][0],f[t][j][1]));
                gmx(dp[i][j],mg1[i][j]+f[t][i][1]-1);
            }
        }
        for(int i=1;i<k;i++){
            for(int p=1;p<k&&i-1+p<k;p++){
                gmx(f[u][max(i,p+1)][0],ff[i][0]+max(f[t][p][0],f[t][p][1]));
            }
        }
    }
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            gmx(f[u][j+1][0],dp[i][j]);
            if(i)   gmx(f[u][j+1][1],dp[i][j]);
            gmx(f[u][max(i+1,j+1)][1],dp[i][j]+1);
        }
    }
    mx[u][0][0]=f[u][0][0];mx[u][0][1]=f[u][0][1];
    for(int i=1;i<k;i++){
        mx[u][i][0]=max(mx[u][i-1][0],f[u][i][0]);
        mx[u][i][1]=max(mx[u][i-1][1],f[u][i][1]);
    }
    vector<vector<int>>().swap(dp);
}
bool mem2;
int main(){
    freopen("tree.in","r",stdin);freopen("tree.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);
    int ans=0;
    for(int i=0;i<k;i++)    gmx(ans,f[1][i][0]);
    printf("%d\n",ans);
}