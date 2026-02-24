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
const int maxn=1e7+10,mod=20101009;
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
int n,m;
int mu[maxn],mud[maxn];
// mud[i]=sum(1,i) j*j*mu[j]
vector<int> p;
void init(){
    const int N=max(n,m);
    mems(mu,0x3f);
    mu[1]=1;
    for(int i=2;i<=N;i++){
        if(mu[i]>1)   mu[i]=-1,p.eb(i);
        for(int j:p){
            if(1ll*i*j>N)   break;
            if(i%j==0){mu[i*j]=0;break;}
            else    mu[i*j]=mu[i]*mu[j];
        }
    }
    for(int i=1;i<=N;i++)  mud[i]=imadd(mud[i-1],1ll*i*i%mod*(mu[i]+mod)%mod);
}
inline int sum(int l,int r){return 1ll*(l+r)*(r-l+1)/2%mod;}
inline int h(int x,int y){return (1ll*x*(x+1)/2)%mod*(1ll*y*(y+1)/2%mod)%mod;}
inline int g(int x,int y){
    // debug("g %d %d\n",x,y);
    int ret=0;
    if(x>y) swap(x,y);
    for(int l=1,r;l<=x;l=r+1){
        r=min(x/(x/l),y/(y/l));
        // debug("%d %d\n",l,r);
        madd(ret,immul(imdel(mud[r],mud[l-1]),h(x/l,y/l)));
        // debug("gret = %d\n",ret);
    }
    // debug("ret = %d\n",ret);
    return ret;
}
inline int f(int x,int y){
    // debug("f %d %d\n",x,y);
    int ret=0;
    if(x>y) swap(x,y);
    for(int l=1,r;l<=x;l=r+1){
        r=min(x/(x/l),y/(y/l));
        // debug("# %d %d\n",l,r);
        madd(ret,immul(sum(l,r),g(x/l,y/l)));
        // debug("fret = %d\n",ret);
    }
    return ret;
}
int main(){
    scanf("%d%d",&n,&m);
    init();
    printf("%d\n",f(n,m)%mod);
}