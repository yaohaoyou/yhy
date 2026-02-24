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
const int maxn=65,mod=1e9+7;
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
int a[maxn];
int C[maxn][maxn];
bool vis[maxn];
int f[maxn][maxn][maxn],g[maxn][maxn][maxn][maxn];  // f[l][r][i] 表示 [l,r] 操作 i 次删完了的方案数，g[l][r][i][j] 表示 [l,r] 操作 i 次最后剩第 j 种颜色的方案数
void init(){
    const int N=60;
    for(int i=0;i<=N;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j],C[i-1][j-1]);}
}
int main(){
    freopen("jam.in","r",stdin);freopen("jam.out","w",stdout);
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n+1;i++) f[i][i-1][0]=1;
    for(int i=1;i<=n;i++)   f[i][i][1]=1,g[i][i][0][a[i]]=1;
    for(int len=2;len<=n;len++){
        for(int l=1,r=len;r<=n;l++,r++){
            for(int i=0;i<=len;i++){
                for(int k=l;k<=r;k++){
                    for(int j=0;j<=i;j++){
                        madd(g[l][r][i][a[k]],1ull*f[l][k-1][j]*imadd(f[k+1][r][i-j],g[k+1][r][i-j][a[k]])%mod*C[i][j]%mod);
                    }
                }
            }
            mems(vis,0);
            for(int i=l;i<=r;i++){
                if(vis[a[i]])   continue;
                vis[a[i]]=true;
                for(int j=1;j<=len;j++)madd(f[l][r][j],g[l][r][j-1][a[i]]);
                // for(int j=0;j<=len;j++) printf("%d %d %d %d : %d\n",l,r,j,a[i],g[l][r][j][a[i]]);
            }
            // for(int j=1;j<=len;j++) printf("%d %d %d : %d\n",l,r,j,f[l][r][j]);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)   madd(ans,f[1][n][i]);
    printf("%d\n",ans);
}