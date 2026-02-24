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
const int maxn=2010,mod=998244353;
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
int n,m,k;
int ans[maxn<<1],fac[maxn<<1],inv[maxn<<1],str[maxn<<1][maxn<<1];
int dp[maxn][maxn];
inline int C(int x,int y){return x<0||y<0||x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void init(){
    const int N=4000;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
    str[0][0]=1;
    for(int i=1;i<=N;i++)
        for(int j=0;j<=N;j++)str[i][j]=imadd(immul(str[i-1][j],j),j?str[i-1][j-1]:0);
}
int main(){
    init();
    scanf("%d%d%d",&n,&m,&k);
    if(k==1){
        printf("1 ");
        for(int i=min(n,m)+1;i<n+m;i++) printf("0 ");
        puts("");
        return 0;
    }
    k--;
    for(int i=0;i<=n&&i<=k;i++)dp[i][k-i]=C(k,i);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
        if(n-i+m-j<k)  continue;
        int w=1ull*C(n,i)*C(m,j)%mod*str[n+m-i-j][k]%mod*fac[k]%mod;
        // printf("str[%d][%d] = %d\n",n+m-i-j,k,str[n+m-i-j][k]);
        // printf("%d %d %d : %d\n",n-i,m-j,n+m-max(i,j),w);
        madd(ans[n+m-max(i,j)],w);
    }
    for(int i=min(n,m);i<n+m;i++)   printf("%d ",ans[i]);
}