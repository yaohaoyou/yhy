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
const int maxn=50,A=200,lgV=60,mod=998244353;
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
ll S,T;
int a[maxn];
int f[maxn][maxn*A],g[maxn][maxn*A];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%lld%lld",&n,&S,&T);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    f[0][0]=1;
    for(int i=0;i<=lgV;i++){
        for(int x=1;x<=n;x++){
            for(int j=2*n;j;j--){
                for(int k=2*n*A;k>=a[x];k--)    madd(f[j][k],f[j-1][k-a[x]]);
            }
        }
        mems(g,0);
        for(int j=0;j<=2*n;j++)for(int k=0;k<=2*n*A;k++)if(((j&1)==((S>>i)&1))&&((k&1)==((T>>i)&1)))madd(g[j>>1][k>>1],f[j][k]);
        memc(f,g);
    }
    printf("%d\n",f[0][0]);
}