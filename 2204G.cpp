#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=310;
int n,m,mod;
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
ull tmp[maxn][maxn];
struct Matrix{
    int a[maxn][maxn];
    int lx,ly;
    Matrix(int _x=0,int _y=0){lx=_x;ly=_y;mems(a,0);}
    inline int* operator[](int x){return a[x];}
    inline void init(){for(int i=1;i<=lx&&i<=ly;i++)a[i][i]=1;}
    inline Matrix operator*(Matrix y){
        assert(ly==y.lx);
        Matrix res(lx,y.ly);mems(tmp,0);
        for(int i=1;i<=lx;i++)
        for(int k=1;k<=y.ly;k++)
                for(int j=1;j<=ly;j++){
                    tmp[i][k]+=1ull*a[i][j]*y[j][k];
                    if((j&15)==15)tmp[i][k]%=mod;
                }
        for(int i=1;i<=lx;i++)for(int j=1;j<=y.ly;j++)res[i][j]=tmp[i][j]%mod;
        return res;
    }
    void print(){for(int i=1;i<=lx;i++,puts(""))for(int j=1;j<=ly;j++)printf("%d ",a[i][j]);}
};
inline int md(int x){return (x%mod+mod)%mod;}
Matrix matt,trans,t,res;
inline Matrix qpow(Matrix x,int y){res=Matrix(x.lx,x.ly);res.init();while(y){if(y&1)res=res*x;x=x*x;y>>=1;}return res;}
int main(){
    scanf("%d%d%d",&n,&m,&mod);
    trans=Matrix(m+m+1,m+m+1);
    for(int i=1;i<=m;i++){
        trans[m][i]=1ull*i*(i+1)/2%mod;
        for(int l=1;l<=i;l++)   trans[l-1][i]=md(-(i-l+1));
        for(int r=1;r<=i;r++)   trans[r+1+m][i]=md(-r);
        trans[m][i+m]=1ull*(m-i+1)*(m-i+2)/2%mod;
        for(int l=i;l<=m;l++)   trans[l-1][i+m]=md(-(m-l+1));
        for(int r=i;r<=m;r++)   trans[r+1+m][i+m]=md(-(r-i+1));
    }
    for(int i=1;i<=m+m+1;i++)   trans[m+m+1][i]=0;
    trans[m+m+1][m+m+1]=trans[m][m+m+1]=1;
    matt=Matrix(1,m+m+1);
    for(int i=1;i<=m;i++)   matt[1][i]=1;
    matt[1][m+1]=1;
    t=matt*qpow(trans,n);
    printf("%d\n",imdel(imadd(t[1][m+m+1],t[1][m]),1));
}