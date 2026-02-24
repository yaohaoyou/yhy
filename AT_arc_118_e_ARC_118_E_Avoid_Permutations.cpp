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
const int maxn=210,mod=998244353;
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
int a[maxn];
int dp[maxn][maxn][maxn][2][2];  // 令 dp_{i,j,k,0/1,0/1} 表示当前在 (i,j)，已经做过了 k 个障碍物，当前这一行/列 有/没有 已经选择放置的障碍
int b[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        if(~a[i])b[a[i]]=i;else a[i]=0;
    int m=count(a+1,a+n+1,0);
    dp[0][0][0][0][0]=1;
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=n+1;j++){
            for(int k=0;k<=m;k++){
                auto f=dp[i][j][k];
                if(j&&j<=n&&!a[i+1]&&!b[j])  madd(dp[i+1][j][k+1][1][1],imadd(f[0][0],f[1][0]));
                if(!a[i+1]||(a[i+1]!=j)){
                    madd(dp[i+1][j][k][bool(a[i+1])][0],imadd(f[0][0],f[1][0]));
                    madd(dp[i+1][j][k][bool(a[i+1])][1],imadd(f[0][1],f[1][1]));
                }
                
                if(i&&i<=n&&!a[i]&&!b[j+1])  madd(dp[i][j+1][k+1][1][1],imadd(f[0][0],f[0][1]));
                if(!a[i]||(a[i]!=j+1)){
                    madd(dp[i][j+1][k][0][bool(b[j+1])],imadd(f[0][0],f[0][1]));
                    madd(dp[i][j+1][k][1][bool(b[j+1])],imadd(f[1][0],f[1][1]));
                }
                // printf("%d %d %d : %d %d %d %d\n",i,j,k,f[0][0],f[0][1],f[1][0],f[1][1]);
            }
        }
    }
    int ans=0,fac=1;
    for(int i=m;~i;i--){
        if(i^m) mmul(fac,m-i);
        int s=immul(dp[n+1][n+1][i][0][0],fac);
        if(i&1) mdel(ans,s);
        else madd(ans,s);
    }
    printf("%d\n",ans);
}