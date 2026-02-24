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
const int maxn=1e5+10,mod=998244353;
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
int a[maxn];
int fac[maxn],inv[maxn];
void init(){
    const int N=1e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
int main(){
    // freopen("net.in","r",stdin);freopen("net.out","w",stdout);
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    if(m==n-1){
        int ans=fac[n-2];
        for(int i=1;i<=n;i++)   mmul(ans,inv[a[i]-1]);
        printf("%d\n",ans);
        return 0;
    }
    if(m==n){
        a[n+1]=n+n-accumulate(a+1,a+n+1,0);
        int ans=fac[n-1];
        for(int i=1;i<=n+1;i++) mmul(ans,inv[a[i]-1]);
        mmul(ans,immul(fac[a[n+1]-1],qpow(2,mod-2)));
        printf("%d\n",ans);
        return 0;
    }
    int sum=n+n-accumulate(a+1,a+n+1,0),I=1;
    for(int i=1;i<=n;i++)   mmul(I,inv[a[i]-1]);
    int ans=1ull*fac[n-1]*sum%mod*(sum+2)%mod*(sum-3)%mod,res=1ull*fac[n-1]*(n-sum)%mod*(sum-3)%mod;
    mmul(ans,I);mmul(ans,qpow(24,mod-2));
    mmul(res,I);mmul(res,qpow(8,mod-2));
    madd(ans,res);
    printf("%d\n",ans);
}