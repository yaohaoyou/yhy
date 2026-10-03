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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e6+10,mod=1e9+7;
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
int n;
ll a[maxn];
inline int id(int x){return (x-1+n)%n+1;}
int main(){
    freopen("tri.in","r",stdin);freopen("tri.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    int ans=0;
    if(n==3){
        // 0 0 0
        ans++;
        // x 0 0
        for(int i=1;i<=n;i++)   madd(ans,a[i]*2);
    }
    // x x 0
    for(int i=1;i<=n;i++)   madd(ans,a[i]*(a[i]-1)/2%mod);
    // x x+1 0
    for(int i=1;i<=n;i++)    madd(ans,a[i]*a[id(i+1)]%mod);
    // x y 0
    for(int i=1;i<=n;i++){
        madd(ans,a[i]*a[id(i+n/2)]%mod);
        madd(ans,a[i]*a[id(i-n/2)]%mod);
    }
    ll s=accumulate(a+1,a+n+1,0ll);
    // x x y
    for(int i=1;i<=n;i++)madd(ans,immul(a[i]*(a[i]-1)/2%mod,(s-a[i])%mod));
    // x y z
    int res=immul(immul(s%mod,s%mod),s%mod);
    for(int i=1;i<=n;i++){
        mdel(res,a[i]*a[i]*a[i]%mod);
        mdel(res,immul(3*a[i]*a[i]%mod,(s-a[i])%mod));
    }
    mmul(res,qpow(6,mod-2));
    madd(ans,res);
    printf("%d\n",ans);
}