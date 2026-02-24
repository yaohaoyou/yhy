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
const int lg=19,V=(1<<lg+1)-1,maxn=V+10,mod=998244353,inv2=(mod+1)>>1,inv4=1ll*inv2*inv2%mod;
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
int a[maxn],g[maxn],k[maxn],p[maxn],G[maxn];
inline void FWT(int *F){
    for(int i=0;i<=lg;i++)
        for(int j=0;j<=V;j++)if(!(j&(1<<i))){
            int x=imadd(F[j],F[j^(1<<i)]),y=imdel(F[j],F[j^(1<<i)]);
            F[j]=x;F[j^(1<<i)]=y;
        }
}
inline void IFWT(int *F){
    for(int i=0;i<=lg;i++)
        for(int j=0;j<=V;j++)if(!(j&(1<<i))){
            int x=immul(imadd(F[j],F[j^(1<<i)]),inv2),y=immul(imdel(F[j],F[j^(1<<i)]),inv2);
            F[j]=x;F[j^(1<<i)]=y;
        }
}
inline void mul(int *F,int *f){for(int i=0;i<=V;i++)mmul(F[i],f[i]);}
int main(){
    for(int i=0;i<=V;i++)G[i]=1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        // mems(g,0);
        scanf("%d",&a[i]);
        g[0]++;g[a[i]]+=2;
        // FWT(g);mul(G,g);
    }
    // for(int i=0;i<=5;i++)   printf("%d ",G[i]);puts("");
    // IFWT(G);printf("%d\n",imdel(G[0],1));exit(0);    
    FWT(g);
    for(int i=0;i<=V;i++)   k[i]=immul(imdel(3*n,g[i]),inv4);
    for(int i=0;i<=V;i++){
        p[i]=(k[i]&1)?mod-1:1;
        mmul(p[i],qpow(3,n-k[i]));
    }
    IFWT(p);
    printf("%d\n",imdel(p[0],1));
}