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
const int maxn=3010,mod=1e9+7;
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
int n,m;
int f[2][maxn][2];
int main(){
    scanf("%d%d",&n,&m);
    if(m==1)    return puts("4"),0;
    n--;
    for(int i=0;i<=n;i++)   f[0][i][!i]=1;
    for(int i=1;i<m;i++){
        for(int j=0;j<=n;j++){
            if(j)   f[i&1][j][1]=f[(i-1)&1][j-1][1];
            else    f[i&1][j][1]=f[(i-1)&1][j+1][0];
            madd(f[i&1][j][1],f[(i-1)&1][j+1][1]);
            madd(f[i&1][j][1],immul(f[(i-1)&1][j][1],2));
            if(j){
                f[i&1][j][0]=imadd(f[(i-1)&1][j+1][0],immul(f[(i-1)&1][j][0],2));
                madd(f[i&1][j][0],f[(i-1)&1][j-1][0]);
            }
            // printf("%d %d\n",f[i&1][j][0],f[i&1][j][1]);
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++)   madd(ans,f[(m-1)&1][i][1]);
    mmul(ans,4);printf("%d\n",ans);
}