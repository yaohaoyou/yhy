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
const int maxn=2010,sqr=55,N=1<<16,mod=998244353;
const int p[16]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
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
pii a[maxn];
int b[maxn],f[2][1<<16][2];  // f[i][j][0/1] 表示前 i 个数中 <sqr 的质数选择状态，是否选择了 >sqr 的数的答案
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);a[i].fi=x;
        for(int j=2;j<=sqr;j++)while(x%j==0)x/=j;
        if(x^1) a[i].se=x;
    }
    sort(a+1,a+n+1,[&](pii x,pii y){return x.se<y.se;});
    for(int i=1;i<=n;i++){
        for(int j=0;j<16;j++)if(a[i].fi%p[j]==0)b[i]|=1<<j;
    }
    f[0][0][1]=1;
    for(int i=1;i<=n;i++){
        mems(f[i&1],0);
        int x=a[i].se?a[i].fi/a[i].se*(a[i].se-1):0;
        for(int j=0;j<N;j++){
            if(a[i].se==a[i-1].se){
                if(f[(i-1)&1][j][0]){
                    madd(f[i&1][j][0],f[(i-1)&1][j][0]);
                    madd(f[i&1][j|b[i]][1],immul(f[(i-1)&1][j][0],x));
                }
                if(f[(i-1)&1][j][1]){
                    madd(f[i&1][j][1],f[(i-1)&1][j][1]);
                    madd(f[i&1][j|b[i]][1],immul(f[(i-1)&1][j][1],a[i].fi));
                }
            }
            else{
                if(f[(i-1)&1][j][0]||f[(i-1)&1][j][1]){
                    int w=f[(i-1)&1][j][0]+f[(i-1)&1][j][1];
                    madd(f[i&1][j][0],w);
                    madd(f[i&1][j|b[i]][1],immul(w,x));
                }
            }
        }
        // for(int j=0;j<N;j++)if(f[i&1][j][0]||f[i&1][j][1])printf("%d %d : %d %d\n",i,j,f[i&1][j][0],f[i&1][j][1]);
    }
    int ans=0;
    for(int i=0;i<N;i++){
        int k=1;for(int j=0;j<16;j++)if(i&(1<<j))mmul(k,immul(p[j]-1,qpow(p[j],mod-2)));
        madd(ans,immul(imadd(f[n&1][i][0],f[n&1][i][1]),k));
    }
    printf("%d\n",ans);
}