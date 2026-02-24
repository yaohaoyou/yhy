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
const int maxn=2010,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int fac[maxn],inv[maxn],pq[maxn];
void init(){
    const int N=2000;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int a,K;
vector<int> f(ll n){
    vector<int> fn(K+1,0);
    if(!n)  return fn;
    if(n&1){
        vector<int> fn1=f(n-1);
        for(int k=0;k<=K;k++){
            for(int j=0;j<=k;j++)   madd(fn[k],immul(C(k,j),fn1[j]));
            mmul(fn[k],a);
            madd(fn[k],a);
        }
        return fn;
    }
    else{
        const ll m=n/2;
        vector<int> fm=f(m);
        int am=qpow(a,m);
        pq[0]=1;for(int i=1;i<=K;i++)pq[i]=immul(pq[i-1],m%mod);
        for(int k=0;k<=K;k++){
            for(int j=0;j<=k;j++)   madd(fn[k],1ull*C(k,j)*pq[k-j]%mod*fm[j]%mod);
            mmul(fn[k],am);madd(fn[k],fm[k]);
        }
        return fn;
    }
}
ll n;
int main(){
    init();
    scanf("%lld%d%d",&n,&a,&K);
    printf("%d\n",f(n)[K]);
}