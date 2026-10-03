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
bool mem1;
const int maxn=5e5+10,mod=1e9+7;
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
inline int calc(ll l,ll r,ll t){return immul((t+r-l)%mod,(r-l+1)%mod);}
bool mem2;
int main(){
    freopen("street.in","r",stdin);freopen("street.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    ll now=0;int ans=0;
    for(int i=1;i<=n;i++){
        ll x,r;scanf("%lld%lld",&x,&r);
        if(i==1){
            madd(ans,calc(x,r,x));
            now=x+(r-x)*2;
            continue;
        }
        if(x<=now+1){
            now+=2;
            madd(ans,calc(x,r,now));
            now+=2*(r-x);
        }
        else{
            now=x;
            madd(ans,calc(x,r,x));
            now+=2*(r-x);
        }
    }
    printf("%d\n",ans);
}