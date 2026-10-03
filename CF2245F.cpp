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
int a[maxn];
int g[maxn][maxn],C[maxn][maxn];
vector<int> f[maxn][maxn];
void matt(int _cases){
    for(int i=0;i<=n+1;i++)for(int j=0;j<=n+1;j++)  g[i][j]=0,f[i][j].clear();
    scanf("%d",&n);
    for(int i=0;i<=n;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    if(accumulate(a+1,a+n+1,0)+count(a+1,a+n+1,-1)>n)return puts("0"),void();
    a[n+1]=-1;
    for(int i=1;i<=n;i++)for(int j=i-1;j<=n;j++)f[i][j].resize(a[j+1]+1);
    for(int i=1;i<=n+1;i++){
        if(f[i][i-1].empty())   f[i][i-1].eb(1);
        else    f[i][i-1][0]=1;
        g[i][i-1]=1;
    }
    for(int len=1;len<=n;len++){
        for(int l=1,r=len;r<=n;l++,r++){
            if(~a[r+1]){
                for(int i=1;i<=a[r+1];i++){
                    for(int p=l;p<=r;p++){
                        if(~a[p])   madd(f[l][r][i],immul(C[r-l][p-l],immul(f[l][p-1][a[p]],f[p+1][r][i-1])));
                        else    madd(f[l][r][i],immul(C[r-l][p-l],immul(g[l][p-1],f[p+1][r][i-1])));
                    }
                    madd(g[l][r],f[l][r][i]);
                }
            }
            else{
                for(int p=l;p<=r;p++){
                    if(~a[p])   madd(g[l][r],immul(C[r-l][p-l],immul(f[l][p-1][a[p]],g[p+1][r])));
                    else    madd(g[l][r],immul(C[r-l][p-l],immul(g[l][p-1],g[p+1][r])));
                }
            }
        }
    }
    printf("%d\n",g[1][n]);
}
bool mem2;
int main(){debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}