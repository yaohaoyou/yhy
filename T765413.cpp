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
const int maxn=5e5+10,lgV=30,mod=998244353;
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
int a[maxn],nx[maxn][40];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=n;i;i--){
        memc(nx[i],nx[i+1]);
        for(int j=0;j<=lgV;j++)if(a[i]&(1<<j))nx[i][j]=i;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        int r=n,res=0;
        for(int j=lgV;~j;j--){
            int x=nx[i][j],y=nx[x+1][j];
            if(!x||x>r)  continue;
            if(y&&y<=r){
                madd(res,immul(r-y+1,(1ll<<j+1)-1));
                r=y-1;if(r<i)break;
            }
            madd(res,immul(r-x+1,1<<j));
        }
        madd(ans,res);
    }
    printf("%d\n",ans);
}