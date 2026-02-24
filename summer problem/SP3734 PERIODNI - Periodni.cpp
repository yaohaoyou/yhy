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
const int maxn=510,maxV=1e6+10,mod=1e9+7;
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
int n,k;
int a[maxn];
pii v[maxn];int cnt;
vector<int> son[maxn];
int f[maxn][maxn];
int fac[maxV],inv[maxV];
void init(){
    int N=1e6;
    fac[0]=1;
    for(int i=1;i<=N;i++)   fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);
    for(int i=N-1;~i;i--)   inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int divide(int l,int r){
    int mn=l;
    for(int i=l;i<=r;i++)if(a[i]<a[mn])mn=i;
    vector<int> vec;
    for(int i=l;i<=r;i++)if(a[i]==a[mn])vec.eb(i);
    v[++cnt]=pii(r-l+1,a[mn]);
    int u=cnt;
    for(int i:vec){if(l<=i-1){int c;son[u].eb(c=divide(l,i-1));v[c].se-=a[mn];}l=i+1;}
    if(vec.back()+1<=r){int c;son[u].eb(c=divide(vec.back()+1,r));v[c].se-=a[mn];}
    return u;
}
void dfs(int u){
    if(son[u].empty()){
        for(int i=0;i<=k;i++)   f[u][i]=1ll*C(v[u].fi,i)*C(v[u].se,i)%mod*fac[i]%mod;
        return;
    }
    int g[maxn],gg[maxn];
    f[u][0];
    for(int t:son[u]){
        // printf("%d %d\n",u,t);
        dfs(t);
        if(t==son[u].front()){memc(g,f[t]);continue;}
        mems(gg,0);
        for(int i=0;i<=k;i++)
            for(int j=0;i+j<=k;j++) madd(gg[i+j],immul(g[i],f[t][j]));
        memc(g,gg);
    }
    // for(int i=0;i<=k;i++)   printf("g %d %d : %d\n",u,i,g[i]);
    for(int i=0;i<=k&&i<=v[u].fi;i++){
        for(int j=0;j<=i;j++)   madd(f[u][i],1ll*g[j]*C(v[u].se,i-j)%mod*C(v[u].fi-j,i-j)%mod*fac[i-j]%mod);
        // printf("f %d %d : %d\n",u,i,f[u][i]);
    }
}
int main(){
    init();
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    divide(1,n);
    dfs(1);
    printf("%d\n",f[1][k]);
}