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
const int maxn=550,mod=998244353;
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
ll n;int m;
int fac[maxn],inv[maxn],f[maxn],I[maxn];
void init(){
    const int N=510;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    for(int i=1;i<=N;i++)I[i]=qpow(i,mod-2);
}
inline int C(ll x,int y){
    if(x<y||x<0||y<0)return 0;
    int res=inv[y];
    for(ll i=x-y+1;i<=x;i++)    mmul(res,i%mod);
    return res;
}
int main(){
    init();
    scanf("%lld%d",&n,&m);
    const int M=m+10;
    int ans=0;
    for(int j=1;j<=m;j++){
        ll k=(n-m)/j+1;
        if(k<=M){
            int sum=0;
            for(int i=1;i<=k;i++){
                madd(sum,C(n-i*j-1,m-j-1));
            }
            if(j==m&&n%m==0)    madd(sum,1);
            mmul(sum,C(m,j));
            if(j&1) madd(ans,sum);
            else mdel(ans,sum);
        }
        else{
            k%=mod;
            for(int i=1;i<=M;i++)   f[i]=imadd(f[i-1],C(n-i*j-1,m-j-1));
            int sum=0;
            for(int i=1;i<=M;i++){
                int x=f[i];
                for(int j=1;j<=M;j++)if(i^j)mmul(x,immul(imdel(k,j),i>j?I[imdel(i,j)]:(mod-I[j-i])));
                madd(sum,x);
            }
            if(j==m&&n%m==0)    madd(sum,1);
            mmul(sum,C(m,j));if(!(j&1))sum=imdel(0,sum);
            madd(ans,sum);
        }
    }
    printf("%d\n",ans);
}