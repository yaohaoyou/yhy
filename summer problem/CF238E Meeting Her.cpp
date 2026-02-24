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
const int maxn=110;
int n,m,K,S,T;
namespace Graph{
    const int maxm=maxn*maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn][maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
pii a[maxn];
int dis[maxn][maxn],f[maxn][maxn];  // f[u][i] 表示当前在 u,坐在第 i 辆车上换乘次数的最小值
bool pro[maxn][maxn],mus[maxn][maxn],g[maxn][maxn];
int buc[maxn];
int main(){
    scanf("%d%d%d%d",&n,&m,&S,&T);
    mems(dis,0x3f);
    for(int i=1;i<=n;i++)   dis[i][i]=0;
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);add(v,u);dis[u][v]=1;}
    scanf("%d",&K);
    for(int i=1;i<=K;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)   dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    for(int i=1;i<=K;i++){
        int s=a[i].fi,t=a[i].se;
        if(dis[s][t]==dis[0][0])    continue;
        mems(buc,0);
        for(int j=1;j<=n;j++){
            pro[i][j]=(dis[s][j]+dis[j][t]==dis[s][t]);
            if(pro[i][j])   buc[dis[s][j]]++;
        }
        for(int j=1;j<=n;j++)if(pro[i][j])mus[i][j]=buc[dis[s][j]]==1;
    }
    mems(f,0x3f);
    for(int i=1;i<=K;i++)if(pro[i][T])f[T][i]=1;
    for(int u=1;u<=n;u++)
        for(int i=1;i<=K;i++)
            go(u,_) deg[t][i]+=(dis[a[i].fi][t]+1+dis[u][a[i].se]==dis[a[i].fi][a[i].se]);
    queue<pii> q;
    for(int d=1;d<=K;d++){
        // printf("d = %d\n",d);z
        for(int i=1;i<=n;i++)for(int j=1;j<=K;j++)if(f[i][j]==d)q.ep(i,j);
        while(!q.empty()){
            int u=q.front().fi,i=q.front().se;q.pop();
            // printf("u = %d %d : %d\n",u,i,f[u][i]);
            if(mus[i][u]){
                for(int j=1;j<=K;j++)if(pro[j][u])f[u][j]=min(f[u][j],f[u][i]+1);
            }
            go(u,_){
                if(dis[a[i].fi][t]+1+dis[u][a[i].se]!=dis[a[i].fi][a[i].se])    continue;
                // printf("%d %d %d : %d %d\n",u,t,i,dis[a[i].fi][u]+1+dis[t][a[i].se],dis[a[i].fi][a[i].se]);
                // printf("%d %d : %d\n",t,i,f[t][i]);
                if(!(--deg[t][i])&&f[t][i]>d) f[t][i]=d,q.ep(t,i);
            }
        }
    }
    int ans=1e9;for(int i=1;i<=K;i++)if(mus[i][S])ans=min(ans,f[S][i]);
    printf("%d\n",ans>K?-1:ans);
}