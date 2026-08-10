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
const int maxn=1e5+10,B=3000,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m;
int f[maxn],phi[maxn],mu[maxn];
vector<int> g[maxn];
int H[maxn/B][maxn/B];
vector<vector<int>> h[maxn];
bool ntp[maxn];
vector<int> p;
void init(){
    n=1e5;phi[1]=mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!ntp[i]) p.eb(i),phi[i]=i-1,mu[i]=-1;
        for(int j:p){
            if(1ll*i*j>n)   break;
            ntp[i*j]=true;
            if(i%j==0){
                phi[i*j]=phi[i]*j;
                break;
            }
            phi[i*j]=phi[i]*phi[j];
            mu[i*j]=mu[i]*mu[j];
        }
    }
    for(int i=1;i<=n;i++)if(mu[i]==-1)mu[i]=mod-1;
    for(int i=1;i<=n;i++){
        int p=immul(i,qpow(phi[i],mod-2));
        for(int j=1;i*j<=n;j++)madd(f[i*j],immul(p,mu[j]));
    }
    // for(int i=1;i<=n;i++)   madd(f[i],f[i-1]);
    g[0].resize(n+1,0);
    for(int i=1;i<=n;i++){
        g[i].resize(n/i+1);
        int s=0;
        for(int j=1;i*j<=n;j++) madd(s,phi[i*j]),g[i][j]=s;
    }
    // for(int i=1;i<=B;i++)for(int j=1;j<=n/B;j++)for(int k=1;k<=n/B;k++)madd(H[j][k],);
    h[B].resize(n/B+1,vector<int>(n/B+1,0));
    for(int i=B+1;i<=n;i++){
        h[i].resize(n/i+1,vector<int>(n/i+1,0));
        for(int j=1;j<=n/i;j++)for(int k=1;k<=n/i;k++)h[i][j][k]=imadd(h[i-1][j][k],1ull*f[i]*g[i][j]%mod*g[i][k]%mod);
    }
    // for(int i=2;i<=n;i++)
    //     for(int j=1;i*j<=n;j++) madd(g[i][j],g[i-1][j]);
}
void matt(int _cases){
    scanf("%d%d",&n,&m);
    int ans=0;
    for(int i=1;i<=min({n,m,B});i++)    madd(ans,immul(f[i],immul(g[i][n/i],g[i][m/i])));
    // for(int i=B+1;i<=min(n,m);i++)    madd(ans,immul(f[i],immul(g[i][n/i],g[i][m/i])));
    for(int l=B+1,r;l<=n&&l<=m;l=r+1){
        r=min(n/(n/l),m/(m/l));
        int i=n/l,j=m/l;
        madd(ans,imdel(h[r][i][j],h[l-1][i][j]));
    }
    printf("%d\n",ans);
}
int main(){init();int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}