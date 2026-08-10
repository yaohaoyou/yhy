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
const int maxn=1000+10,mod=998244353;
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
int n,ans;
int a[maxn],s[maxn],inv[maxn],dp[maxn][maxn];  // dp[i][j] 表示前 i 个数分 j 段的答案
int F[maxn],I[maxn],C[maxn][maxn],c[maxn];
void init(){
    const int N=maxn-10;
    // F[0]=1;for(int i=1;i<=N;i++)F[i]=immul(F[i-1],i);
    // I[N]=qpow(F[N],mod-2);for(int i=N-1;~i;i--)I[i]=immul(I[i+1],i+1);
    for(int i=0;i<=N;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)    C[i][j]=imadd(C[i-1][j],C[i-1][j-1]);
    }
}
int main(){
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   inv[i]=qpow(i,mod-2);
    for(int i=1;i<=n;i++)   s[i]=imadd(s[i-1],a[i]);
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++)   c[j]=imdel(s[i],s[j]);
        for(int j=1;j<=i;j++){
            int sum=imdel(s[i],s[j-1]);
            for(int k=j-1;k<i;k++){
                if(k)   madd(dp[i][j],imadd(dp[k][j-1],1ull*C[k-1][j-2]*inv[i-k]%mod*imdel(s[i],s[k])%mod));
                else    madd(dp[i][j],imadd(dp[k][j-1],1ull*inv[i-k]*imdel(s[i],s[k])%mod));
                if(j==1)  break;
            }
        }
    }
    for(int i=1;i<=n;i++)   printf("%d ",immul(dp[n][i],inv[i]));puts("");
    for(int i=1;i<=n;i++)   madd(ans,immul(dp[n][i],inv[i]));
    printf("%d\n",immul(ans,qpow(qpow(2,n-1),mod-2)));
}
// 332,748,123