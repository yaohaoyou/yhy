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
const int maxn=1e5+10,mod=1e9+7;
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
int dp[maxn];
void dfs1(int u,int ft){
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        dfs1(t,u);dp[u]+=dp[t];
    }
    if(!dp[u])  dp[u]=1;
}
int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs1(1,0);
    if(deg[1]==1)   dp[1]++;
    int ans=0;
    for(int i=1;i<=n;i++){
        if(deg[i]==1)   madd(ans,qpow(2,n-dp[1]+1));
        else    madd(ans,qpow(2,n-dp[1]));
    }
    printf("%d\n",ans);
}