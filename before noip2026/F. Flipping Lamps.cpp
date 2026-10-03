#include<set>
#include<map>
#include<queue>
#include<ctime>
#include<cstdio>
#include<vector>
#include<random>
#include<cassert>
#include<cstring>
#include<algorithm>
#define fi first
#define se second
#define ep emplace
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char ch=getchar();int f=1,x=0;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=1e4+10,mod=998244353;
ll n,m,r,fac[N],inv[N],g[N],c[N];int f[N][N];
ll qp(ll a,ll b){
    ll r=1;
    for(;b;b>>=1,a=a*a%mod)
        if(b&1) r=r*a%mod;
    return r;
}
ll C(ll n,ll m){return n>=m&&m>=0?fac[n]*inv[m]%mod*inv[n-m]%mod:n==m;}
void add(ll &x,ll y){((x+=y)>=mod)&&(x-=mod);}
void add(int &x,int y){((x+=y)>=mod)&&(x-=mod);}
ll F(int i,int j){
    ll res=0;swap(i,j);
    rep(k,0,min(i,j)){
        ll t=C(i,k)*C(n-i,j-k)%mod;
        if(k&1) t=mod-t;
        add(res,t);
    }
    return res;
}
void misaka(int _ID){
    n=read(),m=read(),r=read();
    fac[0]=1;
    rep(i,1,n) fac[i]=fac[i-1]*i%mod;
    inv[n]=qp(fac[n],mod-2);
    per(i,n-1,0) inv[i]=inv[i+1]*(i+1)%mod;
    rep(i,0,n) f[0][i]=F(0,i),f[i][n]=F(i,n);
    rep(i,1,n)per(j,n-1,0) f[i][j]=((ll)f[i-1][j]+f[i-1][j+1]+f[i][j+1])%mod;
    rep(i,0,n) g[i]=f[r][i];
    rep(i,1,m) c[read()]++;
    rep(i,0,n)rep(j,0,n) (g[j]*=qp(f[i][j],c[i]))%=mod;
    ll ans=0;
    rep(i,0,n) add(ans,g[i]*C(n,i)%mod);
    printf("%lld",ans*qp(qp(2,n),mod-2)%mod);
}
bool __ed;
signed main(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=1;
    rep(i,1,T) misaka(i);
    return 0;
}
