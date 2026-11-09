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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=310,mod=998244353;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
inline mit qpow(mit x,int y){mit res=1;while(y){if(y&1)res*=x;x*=x;y>>=1;}return res;}
int n;
mit ans;
char a[maxn];
int lim[maxn];
mit f[maxn][maxn][maxn];  // f[i][j][k] 表示前 i 段和为 j，最后选了 <=k 的方案数
mit fac[maxn],inv[maxn];
void init(){
    n=300;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1);
}
inline mit C(int x,int y){return x<0||y<0||x<y?mit(0):fac[x]*inv[y]*inv[x-y];}
bool mem2;
int main(){
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%s",&n,a+1);reverse(a+1,a+n+1);
    for(int i=2,j=0,c=0;i<=n;i++){
        if(a[i]=='B')   j++;
        else    lim[j]=++c;
    }
    const int c0=count(a+1,a+n+1,'R');
    for(int i=lim[0];i<=c0;i++) fll(f[0][i],1,c0+1);
    for(int i=1;i<=min(c0,n-c0-1);i++){
        for(int j=lim[i];j<=c0;j++){
            for(int k=c0;k;k--){
                f[i][j][k]+=f[i][j][k+1];
                for(int x=1;x<=i&&x*k<=j;x++)if(lim[i-x]<=j-x*k)f[i][j][k]+=f[i-x][j-x*k][k+1]*inv[x];else break;
            }
        }
    }
    for(int i=0;i<=min(c0,n-c0-1);i++)if(f[i][c0][1])ans+=f[i][c0][1]*fac[i]*C(n-c0-1,i);
    printf("%d\n",ans);
}