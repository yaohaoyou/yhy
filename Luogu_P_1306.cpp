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
const int maxn=1e9+10,mod=1e8;
int n,m;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace FastMod;
struct Matrix{
    int a[2][2];
    inline void clear(){mems(a,0);}
    inline void init(){clear();a[0][0]=a[1][1]=1;}
    Matrix operator*(Matrix x)const{
        Matrix res;res.clear();
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    madd(res.a[i][j],immul(a[i][k],x.a[k][j]));
        return res;
    }
    inline void print(){printf("%d %d\n%d %d\n",a[0][0],a[0][1],a[1][0],a[1][1]);}
};
inline Matrix qpow(Matrix x,int y){
    Matrix res;res.init();
    if(y<=0)    return res;
    while(y){
        if(y&1) res=res*x;
        x=x*x;
        y>>=1;
        // res.print();puts("");x.print();puts("\n");
    }
    return res;
}
Matrix base,tmp;
int main(){
    base.a[0][0]=base.a[0][1]=base.a[1][0]=1;base.a[1][1]=0;
    scanf("%d%d",&n,&m);
    Matrix res=qpow(base,__gcd(n,m)-2);
    tmp.a[0][0]=tmp.a[1][0]=1;tmp.a[0][1]=tmp.a[1][1]=0;
    res=res*tmp;
    printf("%d\n",res.a[0][0]);
}
// 1 1 2 3 5 8