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
const int maxn=5010,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m;
int a[maxn],p[maxn],b[maxn],fac[maxn],buc[maxn];
int rk(){
    mems(buc,0);
    int res=1;
    for(int i=1;i<=n;i++){
        for(int j=a[i];j<=n;j++)    buc[j]++;
        if(a[i]>=buc[i]){
            // printf("%d %d\n",a,a[i]-buc[i]);
            madd(res,immul(a[i]-buc[a[i]],fac[n-i]));
        }
    }
    // for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    // printf("res = %d\n",res);
    return res;
}
int main(){
    scanf("%d%d",&n,&m);
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=immul(fac[i-1],i);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i]);
    iota(a+1,a+n+1,1);
    int ans=0;
    for(int i=0;i<m;i++){
        madd(ans,rk());
        memc(b,a);
        for(int j=1;j<=n;j++)a[j]=p[b[j]];
    }
    printf("%d\n",ans);
}