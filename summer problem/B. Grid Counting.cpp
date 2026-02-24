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
const int maxn=2e5+10,mod=998244353;
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
int a[maxn],b[maxn],fac[maxn],inv[maxn];
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void init(){
    const int N=2e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);
    for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int sum=0;
    for(int i=1;i<=n;i++)   sum+=a[i];
    if(sum^n)   return puts("0"),void();
    int m=n/2+(n&1);
    for(int i=n;i>m;i--)    b[i]=0;
    b[m]=2-(n&1);
    for(int i=m-1;i;i--)b[i]=b[i+1]+2;
    int s=0,ans=1;
    for(int i=n;i;i--){
        if(i==1)    b[i]-=2,a[i]-=2;
        b[i]-=s;
        if(a[i]>b[i]||a[i]<0||b[i]<0)   return puts("0"),void();
        s+=a[i];
        mmul(ans,C(b[i],a[i]));
        // printf("%d %d\n",a[i],b[i]);
    }
    printf("%d\n",ans);
}
int main(){init();int T;scanf("%d",&T);while(T--)matt();}