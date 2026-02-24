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
    inline int sqr(int x){return immul(x,x);}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m;
int l[maxn],r[maxn],inv[maxn];
int f[maxn][maxn],g[maxn],sf[maxn],h[maxn],ans[maxn],P[maxn];  // f[i][j] 表示 i 是 j 的祖先的概率
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   f[i][i]=1;
    inv[1]=1;for(int i=2;i<=n;i++)inv[i]=immul(mod-mod/i,inv[mod%i]);
    for(int i=2;i<=n;i++)   scanf("%d%d",&l[i],&r[i]);
    for(int i=1;i<=n;i++){
        mems(sf,0);sf[i]=1;
        for(int j=i+1;j<=n;j++){
            int v=inv[r[j]-l[j]+1];
            madd(f[i][j],immul(imdel(sf[r[j]],sf[l[j]-1]),v));
            sf[j]=imadd(sf[j-1],f[i][j]);
        }
    }
    scanf("%d",&m);
    while(m--){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);if(u==v) continue;
        for(int i=n;i;i--){
            madd(g[i],immul(immul(f[i][u],f[i][v]),w));
            madd(ans[i],immul(imadd(f[i][u],f[i][v]),w));
        }
    }
    for(int i=n;i;i--)for(int j=i+1;j<=n;j++)mdel(g[i],immul(g[j],sqr(f[i][j])));
    for(int i=2;i<=n;i++){
        int P=0;
        for(int j=i;j<=n;j++) madd(P,immul(g[j],f[i][j]));
        mdel(ans[i],imadd(P,P));
    }
    for(int i=2;i<=n;i++)   printf("%d ",ans[i]);
}