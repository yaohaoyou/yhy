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
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn],s[maxn],fac[maxn],inv[maxn];
int f[maxn][maxn],g[maxn][maxn];  // f[i][j] 表示前 i 个人有 j 个人还没投的方案数,g[i][j] 表示前 i 组有 j 个人还没投的方案数
vector<int> v[maxn];
void init(){
    const int N=200;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int A(int x,int y){return 1ull*fac[x]*inv[x-y]%mod;}
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){int x;scanf("%d",&x);v[x].eb(a[i]);s[x]+=a[i];}
    int sum=0;
    g[0][0]=1;
    for(int i=1;i<=n;i++){
        mems(f,0);f[0][0]=1;
        for(int j=1;j<=v[i].size();j++)
            for(int k=0;k<=j;k++)
                for(int l=0;l<=v[i][j-1]&&l<=k+1;l++)   madd(f[j][k+1-l],immul(f[j-1][k],A(k+1,l)));
        for(int j=0;j<=sum;j++)
            for(int k=0;k<=v[i].size();k++)
                madd(g[i][j+k],immul(g[i-1][j],f[v[i].size()][k]));
        sum+=v[i].size();
    }
    int ans=0;
    for(int i=0;i<=n;i++){
        if(i&1) mdel(ans,immul(g[n][n-i],fac[n-i]));
        else madd(ans,immul(g[n][n-i],fac[n-i]));
        printf("%d\n",immul(g[n][n-i],fac[n-i]));
    }
    for(int i=1;i<=n;i++)   mmul(ans,inv[v[i].size()]);
    printf("%d\n",ans);
}