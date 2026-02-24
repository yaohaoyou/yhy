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
const int maxn=810,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m;
int a[maxn],dp[maxn][maxn],f[maxn],g[maxn],fac[maxn],inv[maxn],i2[maxn];
inline int I(int x){return qpow(x,mod-2);}
void init(){
    const int N=200;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    i2[0]=1;for(int i=1;i<=N;i++)i2[i]=immul(i2[i-1],(mod+1)>>1);
    inv[N]=I(fac[N]);
    for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline int calc(int x){return 1ull*fac[x+x]*inv[x]%mod*i2[x]%mod;}
int llim;
inline void DP(int lim){
    mems(dp,0);
    {
        dp[0][0]=1;
        for(int i=1;i<m;i++){
            dp[i][0]=1;
            int l=lower_bound(a+1,a+m+1,lim-a[i+1])-a,c=i+1-l;
            if(c<0) continue;
            for(int j=0;j<=n;j++){
                if(!dp[i][j])   continue;
                madd(dp[i+1][j],dp[i][j]);
                if(j+j<c) madd(dp[i+1][j+1],immul(dp[i][j],c-j-j));
            }
        }
    }
    mems(g,0);
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            int w=1ull*dp[m][j]*calc(n-j)%mod;
            if((i&1)^(j&1)) mdel(g[i],immul(C(j,i),w));
            else madd(g[i],immul(C(j,i),w));
        }
    }
    for(int i=n-1;i;i--)    madd(g[i],g[i+1]);
    for(int i=1;i<=n;i++)    madd(f[i],immul(g[i],lim-llim));
    llim=lim;
}
int main(){
    freopen("candy.in","r",stdin);freopen("candy.out","w",stdout);
    init();
    scanf("%d",&n);m=n<<1;
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    sort(a+1,a+m+1);
    vector<int> vec;
    for(int i=1;i<=m;i++)for(int j=i+1;j<=m;j++)vec.eb(a[i]+a[j]);
    sort(vec.begin(),vec.end());
    for(int i:vec)  DP(i);
    reverse(f+1,f+n+1);
    for(int i=1;i<=n;i++)    printf("%d ",f[i]);puts("");
}