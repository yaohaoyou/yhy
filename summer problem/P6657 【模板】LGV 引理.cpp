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
const int maxn=2e6+10,maxm=110,mod=998244353;
int n,m;
int a[maxm],b[maxm],c[maxm][maxm];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
int fac[maxn],inv[maxn];
void init(){
    const int N=2e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);
    for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline int f(int x0,int y0,int x1,int y1){return x0>x1?0:C(x1-x0+y1-y0,x1-x0);}
inline int det(){
    int res=1;
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            while(c[i][i]){
                int x=c[j][i]/c[i][i];
                for(int k=i;k<=m;k++)   mdel(c[j][k],immul(x,c[i][k]));
                swap(c[i],c[j]);res*=-1;
            }
            swap(c[i],c[j]);res*=-1;
        }
    }
    (res==-1)&&(res+=mod);
    for(int i=1;i<=m;i++)   mmul(res,c[i][i]);
    return res;
}
void matt(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)   scanf("%d%d",&a[i],&b[i]);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            c[i][j]=f(a[i],1,b[j],n);
    printf("%d\n",det());
}
int main(){init();int T;scanf("%d",&T);while(T--)matt();}