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
const int maxn=510;
int n,m,mod;
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
int C[maxn][maxn];
int f[2][maxn],g[2][maxn][maxn];
// f[0][i] 表示有 i 个人和 i 个位置的 (a,b) 方案数，f[1][i] 表示贡献和
// g[0][i][j](i>j) 表示有 i 个位置和 j 个人的 (a,b) 方案数，g[1][i][j] 表示贡献和
void init(){
    const int N=500;
    for(int i=0;i<=N;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}
}
inline int S(int l,int r){return l>r?0:1ull*(l+r)*(r-l+1)/2%mod;}
int main(){
    scanf("%d%d%d",&n,&m,&mod);
    init();
    f[0][0]=g[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            madd(f[0][i],1ull*C[i-1][j-1]*f[0][j-1]%mod*f[0][i-j]%mod*(i+1)%mod);
            madd(f[1][i],1ull*C[i-1][j-1]*f[0][j-1]%mod*f[0][i-j]%mod*(S(1,j-1)+S(1,i-j))%mod);
            madd(f[1][i],1ull*C[i-1][j-1]*f[0][j-1]%mod*f[1][i-j]%mod*(i+1)%mod);
            madd(f[1][i],1ull*C[i-1][j-1]*f[1][j-1]%mod*f[0][i-j]%mod*(i+1)%mod);
        }
        g[0][i][i]=f[0][i];g[1][i][i]=f[1][i];
    }
    for(int i=1;i<=n;i++)   g[0][i][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            madd(g[0][i][j],g[0][i-1][j]);
            madd(g[1][i][j],g[1][i-1][j]);
            for(int k=1;k<=j;k++){
                madd(g[0][i][j],1ull*C[j][k]*f[0][k]%mod*g[0][i-k-1][j-k]%mod);
                madd(g[1][i][j],1ull*C[j][k]*f[1][k]%mod*g[0][i-k-1][j-k]%mod);
                madd(g[1][i][j],1ull*C[j][k]*f[0][k]%mod*g[1][i-k-1][j-k]%mod);
            }
        }
    }
    printf("%d\n",g[1][n][m]);
}