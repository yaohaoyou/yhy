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
const int maxx=12,maxn=1010,V=55*maxn,maxV=V+10,mod=998244353;
int fib[maxn]={0,1,1};
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
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
int n,x,m;
int f[maxV],g[maxn][maxV];  // f[i] 表示价值为 i 的成本，g[i][j] 表示放了 i 个芯片的总价值为 j 的方案数
int a[maxx*10],b[maxV*10];
int main(){
    for(int i=3;i<=1000;i++)    fib[i]=fib[i-1]+fib[i-2];
    scanf("%d%d%d",&n,&x,&m);
    mems(f,0x3f);f[0]=0;
    for(int i=0;i<=V;i++){
        for(int j=1;1;j++){
            if(fib[j]>i)    break;
            gmn(f[i],f[i-fib[j]]+1);
        }
    }
    g[0][0]=1;
    for(int i=1;i<=x;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=V;k++)
                madd(g[j][k],g[j-1][k-fib[i]]);
        }
    }
    int ans=0;
    for(int i=0;i<=V;i++)if(f[i]==m)madd(ans,g[n][i]);
    printf("%d\n",ans);
}