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
const int maxn=5010,mod=998244353;
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
int n,p;
int f[maxn][maxn],sf[maxn][maxn],C[maxn][maxn];  // f[i][j] 表示 i 个数和为 j 的方案数
int main(){
    scanf("%d%d",&n,&p);
    for(int i=0;i<=n;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}
    f[0][0]=1;fill(sf[0],sf[0]+n+1,1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(j<=p-2)  f[i][j]=sf[i-1][j-1];
            else    f[i][j]=imdel(sf[i-1][j-1],sf[i-1][j-(p-2)-1]);
            sf[i][j]=imadd(sf[i][j-1],f[i][j]);
            // for(int k=1;k<=p-2&&k<=j;k++)   madd(f[i][j],f[i-1][j-k]);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=n-i;j<=i-p;j++)
            if(j%p!=i%p)    madd(ans,immul(f[n-i][j],C[n][i]));
    mmul(ans,p-1);
    debug("%d\n",ans);
    int res=1;
    for(int i=1;i<=n;i++)   res=imdel(qpow(p-1,i-1),res);
    madd(ans,res);
    printf("%d\n",imdel(qpow(p-1,n),ans));
}