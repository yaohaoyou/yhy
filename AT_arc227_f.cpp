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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10,sqrn=1010,mod=998244353;
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
int f[maxn][sqrn];  // f[i][j] 表示 i 个数分成了 j 个连续段的方案数
bool mem2;
int main(){
    debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    f[0][0]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=1000&&i+j+j<=n;j++){
            madd(f[i+j+j][j],f[i][j]);
            if(i+j+j+1<=n){
                madd(f[i+j+j+1][j],immul(f[i][j],j+j));
                if(j)   madd(f[i+j+j+1][j-1],immul(f[i][j],j-1));
                madd(f[i+j+j+1][j+1],immul(f[i][j],j+1));
            }
        }
    }
    int ans=0;
    for(int i=n;i>0;i-=2)   madd(ans,f[i][1]);
    printf("%d\n",imadd(immul(ans,qpow(2,mod-2)),!(n&1)));
}