#include<bits/stdc++.h>
#define db double
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
const int maxn=60,mod=998244353,inv2=(mod+1)>>1;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
int n;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int siz[maxn];
db f[maxn][maxn],g[maxn][maxn];
ll C[maxn][maxn];
void init(){
    const int N=maxn-10;
    for(int i=0;i<=N;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];}
}
void dfs(int u,int ft){
    f[u][0]=1;
    db ff[maxn];
    siz[u]=1;
    go(u,l){
        int t=e[l].to;
        if(t==ft)   continue;
        dfs(t,u);
        for(int i=0;i<=siz[t];i++){
            g[t][i]=0;
            if(i)g[t][i]+=i*f[t][i-1];
        }
        db j=0;
        for(int i=siz[t]-1;~i;i--){
            j+=f[t][i]/2.0;
            g[t][i]+=j;
        }
        for(int i=0;i<=siz[u]+siz[t];i++)ff[i]=0;
        for(int i=0;i<=siz[u];i++)
            for(int j=0;j<=siz[t];j++)
                ff[i+j]+=f[u][i]*g[t][j]*C[i+j][i]*C[siz[u]-i-1+siz[t]-j][siz[t]-j];
        for(int i=0;i<=siz[u]+siz[t];i++)f[u][i]=ff[i];
        siz[u]+=siz[t];
    }
}
int main(){
    init();
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)for(int k=0;k<=n;k++)f[j][k]=0;
        dfs(i,0);
        for(int j=1;j<n;j++)   f[i][0]/=j;
        printf("%.10lf\n",f[i][0]);
    }
}