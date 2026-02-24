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
const int maxn=210,lim=200*200;
inline void gmx(ll &x,ll y){(x<y)&&(x=y);}
int n,m,k;
int co[maxn],val[maxn];
namespace Graph{
    const int maxm=2010;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
ll dp[maxn][lim+10],f[maxn][maxn][maxn][2];  // dp[u][i] 表示到达 u 时代价和为 i 的最大贡献,f[u][i][j][0/1] 表示性价比最高的点为 u，当前在 i，代价和 %m=j，是否经过 u 的贡献
inline bool cmp(int x,int y){return 1ll*val[x]*co[y]<1ll*val[y]*co[x];}
void bfs(){
    mems(dp,-0x3f);dp[1][0]=0;for(int i=1;i<=lim;i++)dp[1][i]=i>=co[1]?dp[1][i-co[1]]+val[1]:0;
    for(int u=1;u<=n;u++){
        for(int i=co[u];i<=lim;i++) gmx(dp[u][i],dp[u][i-co[u]]+val[u]);
        go(u,_){
            for(int i=0;i<=lim;i++) gmx(dp[t][i],dp[u][i]);
        }
    }
}
void bfs2(int s){
    if(cmp(s,1))    return;
    m=co[s];k=val[s];
    for(int i=0;i<m;i++)f[s][0][i][0]=0;
    for(int u=0;u<=n;u++){
        if(cmp(s,u))    continue;
        bool o=u>=s;
        for(int i=0,r=__gcd(co[u],m);i<r;i++){
            for(int p=i,l=0;l<=2;p=(p+co[u])%m,l+=(p==i)){
                gmx(f[s][u][(p+co[u])%m][o],f[s][u][p][o]+val[u]-1ll*(p+co[u])/m*k);
            }
        }
        go(u,_){
            if(cmp(s,t))    continue;
            for(int i=0;i<m;i++)
                if(t^s) gmx(f[s][t][i][o],f[s][u][i][o]);
                else gmx(f[s][t][i][1],f[s][u][i][0]);
        }
    }
}
void data(){
    srand(time(0));
    n=200;m=2000;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++)   printf("%d %d\n",200,1000000000);
    for(int i=1;i<=m;i++){int x=rand()%n+1,y=rand()%n+1;if(x>y)swap(x,y);printf("%d %d\n",x,y);}
    int q=2e5;
    printf("%d\n",q);
    while(q--){int p=rand()%n+1,r=1ll*rand()*rand()%1000000000+1;printf("%d %d\n",p,r);}
    exit(0);
}
int main(){
    // data();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",&co[i],&val[i]);
    add(0,1);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);add(u,v);}
    bfs();
    mems(f,-0x3f);
    for(int i=1;i<=n;i++)   bfs2(i);
    int q;scanf("%d",&q);
    while(q--){
        int p,r;scanf("%d%d",&p,&r);
        if(r<=lim)  printf("%lld\n",dp[p][r]);
        else{
            ll ans=0;
            for(int i=1;i<=n;i++)   gmx(ans,f[i][p][r%co[i]][1]+1ll*r/co[i]*val[i]);
            printf("%lld\n",ans);
        }
    }
}