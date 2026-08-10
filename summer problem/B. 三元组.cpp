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
const int maxn=1e7+10,V=1e7,mod=998244353;
namespace FastMod{
    inline void mdel(int &x,int y){(y<0)&&(y+=mod);x-=y;(x<0)&&(x+=mod);}
    inline void madd(int &x,int y){(y<0)&&(y+=mod);x+=y;(x>=mod)&&(x-=mod);}
    inline void mmul(int &x,int y){(y<0)&&(y+=mod);x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,ans;
int a[maxn],b[maxn],c[maxn];
int buc[maxn<<1];
unsigned seed;
unsigned get(unsigned &x)
{
    x^=x<<13;
    x^=x>>17;
    x^=x<<5;
    return x%10000000;
}
void solve(){
    for(int i=0,s=n;i<=V+V;i++){
        if(!buc[i]) continue;
        s-=buc[i];
        mdel(ans,2ll*buc[i]*s%mod*(i-V)%mod);
        mdel(ans,1ll*buc[i]*buc[i]%mod*(i-V)%mod);
    }
}
int main()
{
    cin>>n>>seed;
    for(int i=1;i<=n;++i){
        a[i]=get(seed);
        b[i]=get(seed);
        c[i]=get(seed);
    }
    for(int i=1;i<=n;i++)   madd(ans,a[i]-c[i]);
    mmul(ans,n+n);
    for(int i=1;i<=n;i++)buc[a[i]-b[i]+V]++;
    solve();
    mems(buc,0);
    for(int i=1;i<=n;i++)buc[a[i]-c[i]+V]++;
    solve();
    mems(buc,0);
    for(int i=1;i<=n;i++)buc[b[i]-c[i]+V]++;
    solve();
    
    // for(int i=1;i<=n;i++)
    //     for(int j=1;j<=n;j++){
            // mdel(ans,min(a[i]-b[i],a[j]-b[j]));
            // mdel(ans,min(a[i]-c[i],a[j]-c[j]));
            // mdel(ans,min(b[i]-c[i],b[j]-c[j]));
            // madd(ans,a[j]-b[i]);
            // madd(ans,a[j]-c[i]);
            // madd(ans,b[j]-c[i]);
        // }
    mmul(ans,qpow(2,mod-2));
    printf("%d\n",ans);
}