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
const int maxn=2e5+10,maxm=1e4+10,mod=998244353,inv2=mod+1>>1;
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
int n,m,r;
int a[maxn];
int F[maxn],G[maxm][maxm];
int buc[maxn];
int fac[maxn],inv[maxn];
void init(){
    const int N=1e4;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    init();
    scanf("%d%d%d",&n,&m,&r);
    for(int i=1;i<=m;i++)   scanf("%d",&a[i]),buc[a[i]]++;
    buc[r]++;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(i&&j)    G[i][j]=imdel(G[i][j-1],imadd(G[i-1][j-1],G[i-1][j]));
            else{
                for(int k=0;k<=j&&k<=i;k++){
                    if(k&1) mdel(G[i][j],immul(C(j,k),C(n-j,i-k)));
                    else    madd(G[i][j],immul(C(j,k),C(n-j,i-k)));
                }
            }
        }
    }
    fill(F,F+n+1,1);
    for(int i=0;i<=n;i++)if(buc[i])for(int j=0;j<=n;j++)mmul(F[j],qpow(G[i][j],buc[i]));
    // for(int i=m;i;i--)for(int j=0;j<=n;j++)mmul(F[j],G[a[i]][j]);
    int ans=0;
    for(int i=0;i<=n;i++)   madd(ans,immul(F[i],C(n,i)));
    mmul(ans,qpow(qpow(2,n),mod-2));
    printf("%d\n",ans);
}