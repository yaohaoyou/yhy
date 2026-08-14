#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=5e5+10,maxk=110,maxq=510,mod=1e9+7;
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
int n,k,q;
int a[maxn];
struct Matrix{
    int a[2][2];
    inline void clear(){mems(a,0);}
    inline void init(){clear();a[0][0]=a[1][1]=1;}
    inline int* operator[](int x){return a[x];}
    #define rep(i) for(int i:{0,1})
    Matrix operator*(int x)const{
        Matrix res;
        res[0][0]=immul(a[0][0],x);
        res[0][1]=immul(a[0][1],x);
        res[1][0]=immul(a[1][0],x);
        res[1][1]=immul(a[1][1],x);
        return res;
    }
    Matrix operator*(Matrix x)const{
        Matrix res;
        res[0][0]=imadd(immul(a[0][0],x[0][0]),immul(a[0][1],x[1][0]));
        res[0][1]=imadd(immul(a[0][0],x[0][1]),immul(a[0][1],x[1][1]));
        res[1][0]=imadd(immul(a[1][0],x[0][0]),immul(a[1][1],x[1][0]));
        res[1][1]=imadd(immul(a[1][0],x[0][1]),immul(a[1][1],x[1][1]));
        // rep(i)rep(j)rep(k)madd(res.a[i][j],immul(a[i][k],x.a[k][j]));
        return res;
    }
    void operator+=(Matrix x){
        madd(a[0][0],x[0][0]);
        madd(a[0][1],x[0][1]);
        madd(a[1][0],x[1][0]);
        madd(a[1][1],x[1][1]);
    }
    Matrix operator+(Matrix x)const{
        Matrix res=*this;res+=x;return res;
    }
    inline void print(){printf("%d %d\n%d %d\n\n",a[0][0],a[0][1],a[1][0],a[1][1]);}
}fib;
int C[maxq][maxq];
Matrix Matt,f[maxn][2],b[maxn];
Matrix h[maxq][maxk];
Matrix g[maxk][maxq];  // g[i][j] 表示前 i 个位选了 j 个当次幂的贡献和
inline Matrix qpow(Matrix x,int y){Matrix res;res.init();while(y){if(y&1)res=res*x;x=x*x;y>>=1;}return res;}
void init(){
    n=500;for(int i=0;i<=n;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=imadd(C[i-1][j-1],C[i-1][j]);}
}
int pq[maxk*maxq];
int main(){
    // freopen("fibxor.in","r",stdin);freopen("fibxor.out","w",stdout);
    fib[0][0]=0;fib[0][1]=fib[1][0]=fib[1][1]=1;
    Matt.clear();Matt[0][1]=1;init();
    scanf("%d%d%d",&n,&k,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),b[i]=qpow(fib,a[i]);
    pq[0]=1;for(int i=1;i<=k*q;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    g[0][0].init();
    for(int o=1;o<=k;o++){
        f[0][0].init();f[0][1].clear();
        for(int i=1;i<=n;i++){
            f[i][0]=f[i-1][0]+f[i-1][1]*b[i];
            f[i][1]=f[i-1][1]+f[i-1][0]*b[i];
        }
        for(int i=0;i<=q;i++){
            g[o][i]+=g[o-1][i]*f[n][0];
            for(int j=0;i+j<=q;j++) g[o][i+j]+=g[o-1][i]*f[n][1]*immul(pq[(o-1)*j],C[i+j][j]);
        }
        for(int i=1;i<=n;i++)   b[i]=b[i]*b[i];
    }
    printf("%d\n",(Matt*g[k][q])[0][0]);
}