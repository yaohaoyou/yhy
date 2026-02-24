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
const int maxn=5010,mod=1e9+7;
int n,x;
int f[maxn][maxn][2];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
int fac[maxn],inv[maxn];
int sum[maxn][2];
void init(){
    const int N=maxn-10;
    fac[0]=1;
    for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);
    for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int A(int x,int y){return x>=y?immul(fac[x],inv[x-y]):0;}
int main(){
    init();
    scanf("%d%d",&n,&x);int y=n-x;
    for(int i=0;i<=x;i++){
        for(int j=0;j<=y;j++){
            // for(int l=0;l<i;l++)    madd(f[i][j][0],f[l][j][0]);
            // for(int l=0;l<j;l++)    madd(f[i][j][0],f[i][l][1]);
            f[i][j][0]=imadd(sum[i][1],sum[j][0]);
            int inv=qpow(i+j,mod-2);
            mmul(f[i][j][0],inv);
            f[i][j][1]=imadd(f[i][j][0],immul(i,inv));
            madd(sum[i][1],f[i][j][1]);
            madd(sum[j][0],f[i][j][0]);
        }
    }
    int ans=f[x][y][0];
    for(int i=1;i<=n;i++)   mmul(ans,i);
    printf("%d\n",ans);
}