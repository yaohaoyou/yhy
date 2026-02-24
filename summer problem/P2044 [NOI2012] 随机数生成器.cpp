#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
ll mod;
namespace FastMod{
    inline void madd(ll &x,ll y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(ll &x,ll y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(ll &x,ll y){x=__int128(x)*y%mod;}
    inline int imadd(ll x,ll y){madd(x,y);return x;}
    inline ll imdel(ll x,ll y){mdel(x,y);return x;}
    inline ll immul(ll x,ll y){mmul(x,y);return x;}
}
using namespace FastMod;
struct Matrix{
    ll a[2][2];int lx,ly;
    Matrix(int x=0,int y=0){lx=x;ly=y;mems(a,0);}
    inline ll* operator[](int x){return a[x];}
    inline void init(){for(int i=0;i<max(lx,ly);i++)a[i][i]=1;}
    inline Matrix operator*(Matrix y){
        Matrix ret(lx,y.ly);
        assert(ly==y.lx);
        for(int i=0;i<lx;i++)
            for(int j=0;j<ly;j++)
                for(int k=0;k<y.ly;k++)    madd(ret[i][k],immul(a[i][j],y[j][k]));
        return ret;
    }
    inline void print(){for(int i=0;i<lx;i++,puts(""))for(int j=0;j<ly;j++)printf("%d ",a[i][j]);puts("");}
};
inline Matrix qpow(Matrix x,ll y){Matrix res=Matrix(x.lx,x.ly);res.init();while(y){if(y&1)res=res*x;x=x*x;y>>=1;}return res;}
int main(){
    ll a,c,x0,n;int g;
    scanf("%lld%lld%lld%lld%lld%d",&mod,&a,&c,&x0,&n,&g);
    Matrix Matt(2,2),beg(2,1);Matt[0][0]=a;Matt[0][1]=c;Matt[1][1]=1;beg[0][0]=x0;beg[1][0]=1;
    printf("%d\n",(qpow(Matt,n)*beg)[0][0]%g);
}