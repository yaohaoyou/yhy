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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=5010,mod=998244353;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
inline mit qpow(mit x,int y){mit res=1;while(y){if(y&1)res*=x;x*=x;y>>=1;}return res;}
int n,m,K;
int a[maxn];
mit fac[maxn],inv[maxn],d[maxn],f[maxn][maxn],g[maxn][maxn];
void init(){
    n=5000;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1);
}
void mul(mit *x,mit *y,mit *res){
    for(int i=0;i<=m;i++)if(x[i])for(int j=0;i+j<=m;j++)if(y[j])res[i+j]+=x[i]*y[j];
}
bool mem2;
int main(){
    freopen("me.in","r",stdin);freopen("me.out","w",stdout);
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    m=accumulate(a+1,a+n+1,0);
    for(int i=1;i<=m;i++)if(i%K==1)d[i]=1;else if(i%K==0)d[i]=mod-1;
    f[0][0]=1;
    for(int i=1;i<=m;i++){
        // mul(f[i-1],d,f[i]);
        for(int j=1;j<=m;j++)f[i][j]=f[i-1][j-1]-(j>=K?f[i-1][j-K]-f[i][j-K]:mit(0));
    }
    for(int i=0;i<=m;i++)for(int j=0;j<=m;j++)f[i][j]*=inv[i];
    // 做 G[n] = \prod F(a[i])
    g[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=a[i]&&k<=j;k++)  g[i][j]+=g[i-1][j-k]*f[k][a[i]];
        }
    }
    mit ans=0;
    for(int i=1;i<=m;i++)ans+=g[n][i]*fac[i];
    printf("%d\n",ans);
}