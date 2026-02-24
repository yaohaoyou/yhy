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
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn];
vector<int> v[maxn];
int f[maxn],g[maxn][maxn],fac[maxn],inv[maxn];
void init(){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=immul(fac[i-1],i);
    inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
    scanf("%d",&n);
    init();
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){int x;scanf("%d",&x);v[x].eb(a[i]);}
    int s=0;
    g[0][0]=1;
    for(int i=1;i<=n;i++){
        int sum=0,m=v[i].size();
        for(int j:v[i]) sum+=j;
        f[0]=1;
        for(int j:v[i]) mmul(f[0],C(sum,j)),sum-=j;
        for(int j:v[i]) sum+=j;
        // printf("f[0] = %d\n",f[0]); 
        for(int j=1;j<=m&&j<=sum;j++)   f[j]=1ull*f[0]*C(m,j)%mod*inv[sum-j]%mod;
        mmul(f[0],inv[sum]);
        for(int j=0;j<=s;j++){
            for(int k=0;k<=m&&k<=sum;k++) madd(g[i][j+k],immul(g[i-1][j],f[k]));
        }
        s+=m;
        // printf("%d %d\n",f[m],g[i][s]);
    }
    int ans=0;
    for(int i=0;i<=n;i++){
        int w=immul(g[n][i],fac[n-i]);
        if(i&1) mdel(ans,w);
        else madd(ans,w);
    }
    printf("%d\n",ans);
}