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
const int maxn=510;
int n,mod;
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
int f[maxn*maxn];  // f[j] 表示倒着放 i 个数有 j 个逆序对的方案数
int g[maxn*maxn],h[maxn*maxn],s[maxn*maxn],C[maxn][maxn];
int fac[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&mod);
    for(int i=0;i<=n;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=immul(fac[i-1],i);
    f[0]=1;g[0]=1;
    int ans=0;
    for(int i=1;i<=n;i++){
        int res=0;
        for(int a=2;a<=i*(i-1)/2;a++){
            if(i^1)madd(res,immul(immul(f[a],h[a-2]),i-1));
            int l=a+max(1,i-a+2)-2-i,r=a-3;
            if(l<=r&&r>=0){
                if(!l)  mdel(res,immul(f[a],s[r]));
                else    mdel(res,immul(f[a],imdel(s[r],s[l-1])));
            }
            // for(int j=max(1,i-a+2);j<i;j++) mdel(res,immul(f[a],h[a+j-2-i]));
        }
        madd(ans,immul(res,immul(C[n][i],fac[n-i])));
        for(int j=0;j<=i*(i-1)/2;j++){
            if(j>=i)    f[j]=imdel(g[j],g[j-i]);
            else    f[j]=g[j];
        }
        g[0]=f[0];for(int j=1;j<=i*(i+1)/2;j++)g[j]=imadd(g[j-1],f[j]);
        h[0]=g[0];for(int j=1;j<=i*(i+1)/2;j++)h[j]=imadd(h[j-1],g[j]);
        s[0]=h[0];for(int j=1;j<=i*(i+1)/2;j++)s[j]=imadd(s[j-1],h[j]);
    }
    printf("%d\n",ans);
}