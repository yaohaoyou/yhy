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
char s[maxn];int b[maxn];
char d[maxn][maxn];
int a[maxn][maxn];
int f[maxn][maxn],g[maxn][maxn];
int sf[2][maxn],sg[2][maxn];
int main(){
    freopen("cat.in","r",stdin);freopen("cat.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%s",d[i]+1);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++){
        int m=0;for(int j=1;j<=n;j++)if(d[i][j]=='L'||d[i][j]=='R')s[++m]=d[i][j],b[m]=a[i][j];
        mems(f,0);mems(g,0);f[0][0]=1;
        for(int j=1;j<=m;j++){
            for(int k=0;k<=j;k++){
                if(s[j]=='L'){
                    int w=immul(f[j-1][k+1],k+1);
                    madd(f[j][k],w);madd(g[j][k],immul(g[j-1][k+1],k+1));madd(g[j][k],immul(w,b[j]));
                    madd(f[j][k],f[j-1][k]);madd(g[j][k],g[j-1][k]);
                }
                else{
                    if(k)   madd(f[j][k],f[j-1][k-1]),madd(g[j][k],g[j-1][k-1]);
                }
            }
        }
        sf[0][i]=accumulate(f[m],f[m]+m+1,0ll)%mod;
        madd(sg[0][i],accumulate(g[m],g[m]+m+1,0ll)%mod);
        mems(f,0);mems(g,0);f[m+1][0]=1;
        for(int j=m;j;j--){
            for(int k=0;k<=m-j+1;k++){
                if(s[j]=='R'){
                    int w=immul(f[j+1][k+1],k+1);
                    madd(f[j][k],w);madd(g[j][k],immul(g[j+1][k+1],k+1));madd(g[j][k],immul(w,b[j]));
                    madd(f[j][k],f[j+1][k]);madd(g[j][k],g[j+1][k]);
                }
                else{
                    if(k)   madd(f[j][k],f[j+1][k-1]),madd(g[j][k],g[j+1][k-1]);
                }
            }
        }
        madd(sg[0][i],accumulate(g[1],g[1]+m+1,0ll)%mod);
        assert(sf[0][i]==accumulate(f[1],f[1]+m+1,0ll)%mod);
    }
    for(int i=1;i<=n;i++){
        int m=0;for(int j=1;j<=n;j++)if(d[j][i]=='U'||d[j][i]=='D')s[++m]=d[j][i],b[m]=a[j][i];
        mems(f,0);mems(g,0);f[0][0]=1;
        for(int j=1;j<=m;j++){
            for(int k=0;k<=j;k++){
                if(s[j]=='U'){
                    int w=immul(f[j-1][k+1],k+1);
                    madd(f[j][k],w);madd(g[j][k],immul(g[j-1][k+1],k+1));madd(g[j][k],immul(w,b[j]));
                    madd(f[j][k],f[j-1][k]);madd(g[j][k],g[j-1][k]);
                }
                else{
                    if(k)   madd(f[j][k],f[j-1][k-1]),madd(g[j][k],g[j-1][k-1]);
                }
            }
        }
        sf[1][i]=accumulate(f[m],f[m]+m+1,0ll)%mod;
        madd(sg[1][i],accumulate(g[m],g[m]+m+1,0ll)%mod);
        mems(f,0);mems(g,0);f[m+1][0]=1;
        for(int j=m;j;j--){
            for(int k=0;k<=m-j+1;k++){
                if(s[j]=='D'){
                    int w=immul(f[j+1][k+1],k+1);
                    madd(f[j][k],w);madd(g[j][k],immul(g[j+1][k+1],k+1));madd(g[j][k],immul(w,b[j]));
                    madd(f[j][k],f[j+1][k]);madd(g[j][k],g[j+1][k]);
                }
                else{
                    if(k)   madd(f[j][k],f[j+1][k-1]),madd(g[j][k],g[j+1][k-1]);
                }
            }
        }
        madd(sg[1][i],accumulate(g[1],g[1]+m+1,0ll)%mod);
        assert(sf[1][i]==accumulate(f[1],f[1]+m+1,0ll)%mod);
    }
    int sum=1,ans=0;
    for(int i=1;i<=n;i++)   mmul(sum,sf[0][i]),mmul(sum,sf[1][i]);
    // for(int i=1;i<=n;i++)   printf("%d %d\n",sf[0][i],sg[0][i]);puts("");
    // for(int i=1;i<=n;i++)   printf("%d %d\n",sf[1][i],sg[1][i]);puts("");
    for(int i=1;i<=n;i++){
        madd(ans,1ull*sum*qpow(sf[0][i],mod-2)%mod*sg[0][i]%mod);
        madd(ans,1ull*sum*qpow(sf[1][i],mod-2)%mod*sg[1][i]%mod);
    }
    printf("%d\n",ans);
}