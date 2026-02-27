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
const int maxn=5010,maxN=1e5+10,mod=998244353;
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
bool mem1;
int n,m;
int a[maxn],b[maxn];
int f[maxn][maxn],sf[maxn][maxn];  // f[i][j] 表示前 i 个数的和为 j 的贡献和
int fac[maxN],inv[maxN];
void init(){
    const int N=1e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
bool mem2;
void matt(int _cases){
    scanf("%d",&n);m=0;
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    int lst=0;
    for(int i=1;i<=n;i++){
        if(!a[i]){b[++m]=lst;lst=0;continue;}
        int j=i;while(j<=n&&a[j])j++;
        lst=(j-i)/2;i=j-1;
    }
    b[++m]=lst;
    int s=accumulate(b+1,b+m+1,0),now=0;
    for(int i=1;i<=m;i++){
        now+=b[i];
        for(int j=0;j<=s;j++){
            f[i][j]=sf[i-1][j];
            if(i==1)    madd(f[i][j],abs(j-now));
            else    madd(f[i][j],immul(C(j+i-1,i-1),abs(j-now)));
            // for(int k=0;k<=j;k++)   madd(f[i][j],immul(C(k+i-2,i-2),abs(j-now)));
        }
        sf[i][0]=f[i][0];
        for(int j=1;j<=s;j++)   sf[i][j]=imadd(sf[i][j-1],f[i][j]);
    }
    printf("%d\n",f[m][s]);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);init();int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}