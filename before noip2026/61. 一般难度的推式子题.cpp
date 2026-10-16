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
const int maxn=2e5+10;
int mod;
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
int fac[maxn],inv[maxn];
void init(){
    const int N=2e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int n;
int a[maxn];
inline pii to(pii x,int k){return pii(x.se-k,x.fi+k);}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&mod);init();
    // for(int x=0;x<=n;x++)for(int y=0;y<=n;y++)b[x][y]=(y!=x+1)&&(y!=x-3);
    // b[0][0]=0;f[0][0]=1;
    // for(int i=0;i<=n;i++){
    //     for(int j=0;j<=n;j++)if(b[i][j]){
    //         f[i][j]=imadd(i?f[i-1][j]:0,j?f[i][j-1]:0);
    //     }
    // }
    // printf("%d\n",f[3][3]);
    n--;
    int ans=0,w=0;
    for(int i=1;i<=n+1;i++){
        // printf("%d ",C(n+n,n)-C(n+n,n-1)-C(n+n,n-i)+C(n+n,n-i-1)*2);
        int res=C(n+n,n),k=-1;
        pii a=to(pii(n,n),1),b=to(pii(n,n),-i);
        while(true){
            if(a.fi>=0&&a.se>=0){if(k==1)madd(res,C(n+n,a.fi));else mdel(res,C(n+n,a.fi));}
            if(b.fi>=0&&b.se>=0){if(k==1)madd(res,C(n+n,b.fi));else mdel(res,C(n+n,b.fi));}
            pii na=pii(-1,-1),nb=pii(-1,-1);
            if(a.fi>=0&&a.se>=0)    nb=to(a,-i);
            if(b.fi>=0&&b.se>=0)    na=to(b,1);
            a=na;b=nb;k*=-1;
            if((a.fi<0||a.se<0)&&(b.fi<0||b.se<0))  break;
        }
        // printf("%d ",res);
        mdel(res,w);
        if(res) madd(ans,immul(res,i-1));
        madd(w,res);
    }
    printf("%d\n",ans);
}