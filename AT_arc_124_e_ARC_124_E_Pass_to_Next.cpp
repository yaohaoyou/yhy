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
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn],f[maxn][2];
inline int s1(int x){return 1ll*x*(x+1)/2%mod;}
inline int s2(int x){return __int128(x)*(x+1)*(2*x+1)/6%mod;}
int dp(int x,int o){
    mems(f,0);
    f[1][o]=1;
    for(int i=1;i<=n;i++){
        int j=i%n+1;
        a[i]-=x;
        madd(f[j][0],immul(f[i][0],s1(a[i])));madd(f[j][0],immul(f[i][1],a[i]+1));
        a[i]+=x;
        madd(f[j][1],immul(f[i][0],imdel(immul(a[i],s1(a[i])),s2(a[i]))));madd(f[j][1],immul(f[i][1],s1(a[i])));
    }
    return imdel(f[1][o],1);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    printf("%d\n",imdel(imadd(dp(0,0),dp(0,1)),imadd(dp(1,0),dp(1,1))));
}