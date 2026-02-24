#include<bits/stdc++.h>
#define ll long long
#define db double
#define eb emplace_back
#define ep emplace
#define pdi pair<db,int>
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=60,maxv=1e5+10;
int n,Q;
int v[maxn],c[maxn];
namespace Graph{
    const int maxm=maxv*maxn;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxv];
    struct edge{int nxt,to;ll w;}e[maxm];
    inline void add(int u,int v,ll w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,ll w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
ll dp[maxv];
queue<int> q;
bool inq[maxv];
void spfa(){
    mems(dp,-0x3f);dp[0]=0;q.ep(0);
    while(!q.empty()){
        int u=q.front();q.pop();
        inq[u]=false;
        go(u,i){
            int t=e[i].to;ll w=e[i].w;
            if(dp[t]<dp[u]+w){
                dp[t]=dp[u]+w;
                if(!inq[t]){inq[t]=true;q.ep(t);}
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&Q);
    pdi mx=pdi(0,0);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&v[i],&c[i]);
        mx=max(mx,pdi(1.0*c[i]/v[i],i));
    }
    int m=v[mx.se],k=c[mx.se];
    mems(dp,-0x3f);dp[0]=0;
    for(int i=1;i<=n;i++){
        if(i==mx.se)    continue;
        for(int p=0,lim=__gcd(v[i],m);p<lim;p++){
            int u=p;
            for(int j=0;j<=2;(u+=v[i])%=m,j+=u==p){
                int t=(u+v[i])%m;ll w=c[i]-1ll*(u+v[i])/m*k;
                // add(u,t,w);
                dp[t]=max(dp[t],dp[u]+w);
            }
        }
    }
    while(Q--){
        ll x;scanf("%lld",&x);
        ll ans=dp[x%m]+x/m*k;
        if(ans<0)   puts("-1");
        else    printf("%lld\n",ans);
    }
}