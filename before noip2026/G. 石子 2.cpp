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
bool mem1;
const int maxn=3e5+10,mod=998244353;
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
char s[maxn];
int a[maxn];
int fac[maxn],inv[maxn];
void init(){
    const int N=3e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline int A(int x,int y){return x<y?0:1ull*fac[x]*inv[x-y]%mod;}
bool mem2;
int main(){
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%s",&n,s+1);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++)if(s[j]!=s[i]){
            for(int k=i+1;k<=n;k++)if(s[k]!=s[i]){
                int res=2ull*fac[k-j-2]*A(n,n-k+j-1)%mod;
                madd(ans,immul(res,a[i]));
            }
        }
    }
    printf("%d\n",ans);
}