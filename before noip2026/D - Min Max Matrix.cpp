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
const int maxn=1e6+10,mod=998244353;
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
bool mem1;
int n,m,k;
int fac[maxn],inv[maxn];
int f[maxn],suf[maxn],I[maxn];
void init(){
    const int N=1e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline int F(int w){
    int ans=0;
    for(int i=1;i<=n;i++){
        int X=immul(qpow(k-w+1,i),qpow(k,n-i)),Y=qpow(w,n-i);
        int w=immul(C(n,i),imdel(qpow(imdel(X,Y),m),qpow(X,m)));
        if(i&1) mdel(ans,w);
        else    madd(ans,w);
    }
    return ans;
}
bool mem2;
void matt(int _cases){
    scanf("%d%d%d",&n,&m,&k);
    int ans=0;
    const int K=n*m+100;
    for(int i=1;i<=K;i++)   f[i]=imadd(f[i-1],F(i));
    suf[K+1]=1;for(int i=K;i;i--)suf[i]=immul(suf[i+1],imdel(k,i));
    I[0]=1;for(int i=1;i<=K;i++)   I[i]=immul(I[i-1],qpow(i,mod-2));
    for(int i=1,pre=1;i<=K;i++){
        int res=1ull*f[i]*pre%mod*suf[i+1]%mod;
        int w=immul(I[i-1],I[K-i]);
        if((i&1)==(K&1))    mmul(res,w);
        else    mmul(res,mod-w);
        // for(int j=1;j<=K;j++)if(i^j){
        //     mmul(res,qpow(imdel(i,j),mod-2));
        //     if(!res)break;
        // }
        madd(ans,res);
        mmul(pre,imdel(k,i));
    }
    printf("%d\n",ans);
}
int main(){init();debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T=1;for(int i=1;i<=T;i++)matt(i);}