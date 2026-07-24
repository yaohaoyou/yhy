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
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
bool mem1;
int n,m;
int f[650][maxn][2];  // f[i][j] 表示前 i 个数和为 j 的方案数
bool mem2;
void matt(int _cases){
    for(int i=0;i<=n;i++)for(int j=0;j<=m+1;j++)f[i][j][0]=f[i][j][1]=0;
    scanf("%d%d",&n,&m);
    if(1ll*n*(n+1)/2>m+1) return n=m=0,puts("0"),void();
    if(n==1)    return printf("%d\n",m),void();
    f[0][0][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;i+j<=m+1;j++){
            madd(f[i][i+j][1],f[i][j][1]);
            madd(f[i][i+j][0],f[i-1][j][1]);
            madd(f[i][i+j][1],f[i-1][j][1]);
        }
    }
    int ans=0;
    for(int i=0;i<=m+1;i++)   madd(ans,immul(f[n][i][0],m+2-i));
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}