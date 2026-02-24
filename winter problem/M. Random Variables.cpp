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
const int maxn=1010;
int n,m,mod;
int a[maxn],C[maxn][maxn];
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
int mp[maxn][maxn];
inline int f(int i,int j,int k){
    if(!i)  return 1;
    if(!j)  return 0;
    if(~mp[i][m-j])  return mp[i][m-j];
    if(i-k-1>=0)   return mp[i][m-j]=imdel(immul(f(i-1,j,k),j),1ull*f(i-k-1,j-1,k)*j%mod*C[i-1][k]%mod);
    else    return mp[i][m-j]=qpow(j,i);
}
void matt(){
    scanf("%d%d",&n,&m);
    int ans=immul(qpow(m%mod,n),n);
    for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)mp[i][j]=-1;
    for(int i=1;i<n;i++){  // 求众数出现次数 <= i 的方案数
        for(int j=0;j<=n;j++)for(int k=0;k<=n/(i+1)+5;k++)mp[j][k]=-1;
        mdel(ans,f(n,m,i));
    }
    printf("%d\n",ans);
}
void init(){
    const int N=1000;
    for(int i=0;i<=N;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}
}
int main(){int T;scanf("%d%d",&T,&mod);init();while(T--)matt();}