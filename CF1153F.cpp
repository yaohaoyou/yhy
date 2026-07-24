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
const int maxn=4010,mod=998244353;
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
int n,k,l;
int f[maxn][maxn],g[maxn][maxn];
int main(){
    scanf("%d%d%d",&n,&k,&l);mmul(l,qpow(n+n+1,mod-2));
    g[0][0]=1;
    for(int i=1;i<=n+n;i++){
        for(int j=0;j<=i&&j<=n;j++){
            if(j){
                f[i][j]=f[i-1][j-1];g[i][j]=g[i-1][j-1];
                if(j-1>=k)  madd(f[i][j],immul(g[i-1][j-1],l));
            }
            if(j+1<i){
                madd(f[i][j],immul(f[i-1][j+1],j+1));madd(g[i][j],immul(g[i-1][j+1],j+1));
                if(j+1>=k)  madd(f[i][j],1ull*g[i-1][j+1]*(j+1)%mod*l%mod);
            }
        }
    }
    printf("%d\n",immul(f[n+n][0],qpow(g[n+n][0],mod-2)));
}