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
const int mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace FastMod;
struct Matrix{
    int a[2][2];int lx,ly;
    Matrix(int x=0,int y=0){lx=x;ly=y;mems(a,0);}
    inline int* operator[](int x){return a[x];}
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
inline Matrix qpow(Matrix x,char *y){
    Matrix base[10],res=Matrix(x.lx,x.ly);res.init();
    int len=strlen(y+1);
    for(int j=len;j;j--){
        if(y[j]!='0'){y[j]--;break;}
        y[j]='9';
    }
    for(int i=len;i;i--){
        res=res*qpow(x,y[i]-'0');
        x=qpow(x,10);
    }
    return res;
}
const int maxn=1e6+10;
char n[maxn],m[maxn];
int a,b,c,d;
int main(){
    scanf("%s%s%d%d%d%d",n+1,m+1,&a,&b,&c,&d);
    Matrix Matt(2,2),beg(2,1);Matt[0][0]=a;Matt[0][1]=b;Matt[1][1]=1;beg[0][0]=1;beg[1][0]=1;
    Matrix Mathew=qpow(Matt,m);
    Matt[0][0]=c;Matt[0][1]=d;
    // Mathew.print();Matt.print();
    Matt=Matt*Mathew;
    // Mathew.print();
    // ((Mathew*Mathew)).print
    printf("%d\n",((Mathew*qpow(Matt,n))*beg)[0][0]);
}