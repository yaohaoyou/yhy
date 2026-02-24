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
const int maxn=2e5+10,B=2000;
bool mem1;
int n,m,k,tot;
int a[maxn],b[maxn];
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
int dp[maxn][2],siz[maxn],fa[maxn],dfsn[maxn];
int f[maxn][maxn/B+10][2],lim[maxn];
int ff[B+10][2];
void dfs1(int u,int ft){
    dfsn[u]=--tot;fa[tot]=dfsn[ft];b[tot]=a[u];
    go(u,i)if(t^ft)dfs1(t,u);
}
void dfs(int u,int ft){
    dp[u][0]=0;dp[u][1]=1;
    go(u,i)if(t^ft){
        dfs(t,u);
        dp[u][0]+=min(dp[t][0],dp[t][1]+k);
        dp[u][1]+=min(dp[t][0],dp[t][1]);
    }
    if(a[u])    dp[u][0]=1e9;
}
bool mem2;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
void dfs2(int u,int ft){
    if(!a[u])   f[u][0][0]=0;
    f[u][1][1]=1;
    siz[u]=1;
    go(u,_)if(t^ft){
        dfs2(t,u);
        lim[u]=(siz[u]+siz[t]+k)/k;
        for(int i=0;i<=lim[u];i++)ff[i][0]=f[u][i][0],ff[i][1]=f[u][i][1],f[u][i][0]=f[u][i][1]=f[0][0][0];
        lim[u]=(siz[u]+k)/k;
        for(int i=0;i<=lim[u];i++){
            for(int j=0;j<=lim[t];j++){
                gmn(f[u][i+j][0],ff[i][0]+min(f[t][j][0],f[t][j][1]));
                gmn(f[u][i+j][1],ff[i][1]+min(f[t][j][0],f[t][j+1][1]));
            }
        }
        siz[u]+=siz[t];
    }
    lim[u]=(siz[u]+k)/k;
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    tot=n+1;dfs1(1,0);
    for(k=1;k<=B&&k<=n;k++){
        mems(dp,0);
        for(int i=1;i<=n;i++){
            dp[i][1]++;
            if(b[i])    dp[fa[i]][0]+=dp[i][1]+k,dp[fa[i]][1]+=dp[i][1];
            else    dp[fa[i]][0]+=min(dp[i][0],dp[i][1]+k),dp[fa[i]][1]+=min(dp[i][0],dp[i][1]);
        }
        if(!b[n])   printf("%d\n",min(dp[n][0],dp[n][1]+k));
        else    printf("%d\n",dp[n][1]+k);
    }
    if(B<n){
        mems(f,0x3f);
        k=B+1;
        dfs2(1,0);
        for(;k<=n;k++){
            int r=(n+k)/k,ans=1e9;
            for(int i=1;i<=r;i++)   gmn(ans,min(f[1][i][0],f[1][i][1])+i*k);
            printf("%d\n",ans);
        }
    }
}