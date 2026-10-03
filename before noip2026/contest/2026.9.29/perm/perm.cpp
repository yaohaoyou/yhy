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
const int maxn=510,mod=998244353;
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
int a[maxn],b[maxn],c[maxn];
int C[maxn][maxn];
int f[2][maxn][maxn],g[maxn][maxn],h[maxn][maxn];
int s[maxn][maxn];
bool mem2;
int main(){
    // freopen("perm.in","r",stdin);freopen("perm.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=0;i<=n;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    for(int i=0;i<n;i++)    scanf("%d",&c[i]);
    f[0][0][0]=1;
    g[0][0]=a[1];h[0][0]=b[1];
    f[1][1][0]=1;
    for(int i=1;i<=n;i++){
        mems(f[(i+1)&1],0);
        for(int j=0;j<=i;j++){
            for(int k=0;k<=i;k++){
                int dp=f[i&1][j][k];if(!dp)continue;
                madd(f[(i+1)&1][j+1][k+1],dp);
                if(k)madd(f[(i+1)&1][j][k],immul(dp,k));
                if(i-k-1>=0)madd(f[(i+1)&1][j][k+1],immul(dp,i-k-1));
                madd(f[(i+1)&1][j][k],dp);
            }
        }
        for(int j=0;j<=i;j++)
            for(int k=0;k<i;k++)madd(g[i][k],immul(f[i&1][j][k],a[j+1])),madd(h[i][k],immul(f[i&1][j][i-1-k],b[j+1]));
    }
    for(int i=0;i<=n;i++)for(int x=0;x<n;x++)
        for(int j=0;j<=n-x-1;j++)   madd(s[i][x],immul(h[i][j],c[j+x+1]));
    for(int i=1;i<=n;i++){
        int ans=0;
        for(int j=0;j<i;j++)    madd(ans,immul(h[i-1][j],immul(a[1],c[j])));
        for(int mx=2;mx<=i;mx++){
            int w=0;
            for(int x=0;x<n;x++)    madd(w,immul(g[mx-1][x],s[i-mx][x]));
            madd(ans,immul(w,C[i-1][mx-1]));
        }
        printf("%d ",ans);
    }
}